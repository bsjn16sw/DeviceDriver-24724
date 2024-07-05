#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project41/FlashMemoryDevice.h"
#include "../Project41/DeviceDriver.cpp"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(TestCaseName, Flash에서Read가5번호출되어야PASS) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.Times(5);

	DeviceDriver dd{ &mk };
	dd.read(0xA);
}

TEST(TestCaseName, Flash에서Read가5번중다르게리턴하는게있으면EXCEPTION) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.WillOnce(testing::Return(1))
		.WillRepeatedly(testing::Return(2));

	DeviceDriver dd{ &mk };

	EXPECT_THROW({
		dd.read(0xA);
		}, ReadFailException);
}