#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
using namespace std::this_thread;
using namespace std::chrono;

namespace {
    TEST(StopwatchTest, TestGetSeconds) {
        Stopwatch w;

        // Start the stopwatch and sleep for 1.5 seconds
        w.start();
        sleep_for(milliseconds(1500));
        w.stop();

        // Check that get_seconds is approximately 1.5
        EXPECT_NEAR(w.get_seconds(), 1.5, 0.1);

        // Sleep for another 1.5 seconds without starting the stopwatch
        sleep_for(milliseconds(1500));

        // Check that get_seconds is still approximately 1.5
        EXPECT_NEAR(w.get_seconds(), 1.5, 0.1);

        // Start the stopwatch again and sleep for 1.5 seconds
        w.start();
        sleep_for(milliseconds(1500));
        w.stop();

        // Check that get_seconds is approximately 3.0
        EXPECT_NEAR(w.get_seconds(), 3.0, 0.1);

        // Reset the stopwatch
        w.reset();

        // Check that get_seconds is 0.0
        EXPECT_NEAR(w.get_seconds(), 0.0, 0.1);
    }

    TEST(ProcessCommunicationTest, RandomProcessToFilter) {
        Manager m;

        // Create RandomProcess, Filter, and Channel
        RandomProcess r("random numbers");
        Filter f("filter");
        Channel link("link");

        // Schedule processes and add channel
        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);

        // Wait for processes to run
        sleep_for(milliseconds(100));

        // Check if Filter's value is within the range of 0 to 1
        double filter_value = f.value();
        ASSERT_GE(filter_value, 0.0);
        ASSERT_LE(filter_value, 1.0);
    }

    TEST(ChannelTest, PredefinitionTest) {
        Manager m;

        Filter f("filter");
        Channel link("link");

        m.schedule(f, 1_ms)
        .add_channel(link)
        .init();
        
        // Perform assertions based on the expected behavior
        // For example, you can check the running average after some steps
        for (int i = 0; i < 100; i++) {
            double test_values[2] = {0.25, 0.75};
            link.send(test_values[i % 2]);
            m.update();
            m.run(1_ms);
        }
        
        // Assuming that the expected running average after 100 steps is 0.5
        ASSERT_DOUBLE_EQ(f.value(), 0.5);
    }

    TEST(IntegratorTest, ComputesIntegralCorrectly) {
        // Arrange
        Manager m;
        double constantValue = 2.0;
        ConstantProcess constantProcess("ConstantProcess", constantValue);
        Integrator integrator("Integrator");
        Channel link("link");

        m.schedule(constantProcess, 70_us)
        .schedule(integrator, 70_us)
        .add_channel(link)
        .init()
        .run(1_ms);

        EXPECT_NEAR(integrator.value(), constantValue * 0.1, 0.15);
    }
}
