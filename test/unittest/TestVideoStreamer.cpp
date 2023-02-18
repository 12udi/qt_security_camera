#include <gtest/gtest.h>
#include <../../src/VideoStreamer.h>

namespace test {

TEST(TestVideoStreamer, TOOGLE_MOTION_OFF){
    using namespace cat::cam;
    VideoStreamer streamer{};
    bool expectOff = true;
    streamer.toggleMotion(expectOff);
    EXPECT_EQ(expectOff, streamer.motionEnabled());
}

TEST(TestVideoStreamer, TOOGLE_MOTION_ON){
    using namespace cat::cam;
    VideoStreamer streamer{};
    bool expectOn = true;
    streamer.toggleMotion(expectOn);
    EXPECT_EQ(expectOn, streamer.motionEnabled());
}

TEST(TestVideoStreamer, TOOGLE_DEVICE_RPI_CAM) {
    using namespace cat::cam;
    VideoStreamer streamer{};
    bool expectOn = false;
    streamer.toggleDevice(expectOn);
    EXPECT_EQ(DEVICE::RPI_CAM, streamer.activeDevId());
}

TEST(TestVideoStreamer, TOOGLE_DEVICE_WEB_CAM) {
    using namespace cat::cam;
    VideoStreamer streamer{};
    bool expectOn = true;
    streamer.toggleDevice(expectOn);
    EXPECT_EQ(DEVICE::WEBCAM_USB, streamer.activeDevId());
}

TEST(TestVideoStreamer, TOOGLE_CONNECTION_ON){
    using namespace cat::cam;
    VideoStreamer streamer{};
    bool expectOn = true;
}

} // end namespace test
