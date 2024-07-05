#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project41/FlashMemoryDevice.h"
#include "../Project41/DeviceDriver.cpp"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(TestCaseName, Flash����Read��5��ȣ��Ǿ��PASS) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.Times(5);

	DeviceDriver dd{ &mk };
	dd.read(0xA);
}

TEST(TestCaseName, Flash����Read��5���ߴٸ��Ը����ϴ°�������EXCEPTION) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.WillOnce(testing::Return(1))
		.WillRepeatedly(testing::Return(2));

	DeviceDriver dd{ &mk };

	EXPECT_THROW({
		dd.read(0xA);
		}, ReadFailException);
}

TEST(TestCaseName, Write��������ִ���Read�ؾ���) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.Times(1)
		.WillRepeatedly(testing::Return(0xFF)); // Avoid exception in dd.write()

	DeviceDriver dd{ &mk };
	dd.write(0xA, 'A');
}

TEST(TestCaseName, Write�Ҷ�����־PASS) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read)
		.WillRepeatedly(testing::Return(0xFF));

	DeviceDriver dd{ &mk };
	dd.write(0xA, 'A');
}

TEST(TestCaseName, Write�Ҷ���������ʾƼ�EXCEPTION) {
	MockFlashMemoryDevice mk;

	EXPECT_CALL(mk, read, (0xA), ())
		.WillRepeatedly(testing::Return('B'));

	DeviceDriver dd{ &mk };

	EXPECT_THROW({
		dd.write(0xA, 'A');
		}, WriteFailException);
}