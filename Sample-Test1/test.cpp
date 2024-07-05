#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project41/FlashMemoryDevice.h"
#include "../Project41/DeviceDriver.cpp"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class TestFixture : public testing::Test {
public:
	MockFlashMemoryDevice mk;
	DeviceDriver dd{ &mk };
};

TEST_F(TestFixture, Flash����Read��5��ȣ��Ǿ��PASS) {
	EXPECT_CALL(mk, read, (0xA), ())
		.Times(5);

	dd.read(0xA);
}

TEST_F(TestFixture, Flash����Read��5���ߴٸ��Ը����ϴ°�������EXCEPTION) {
	EXPECT_CALL(mk, read, (0xA), ())
		.WillOnce(testing::Return(1))
		.WillRepeatedly(testing::Return(2));

	EXPECT_THROW({
		dd.read(0xA);
		}, ReadFailException);
}

TEST_F(TestFixture, Write��������ִ���Read�ؾ���) {
	EXPECT_CALL(mk, read, (0xA), ())
		.Times(1)
		.WillRepeatedly(testing::Return(0xFF)); // Avoid exception in dd.write()

	dd.write(0xA, 'A');
}

TEST_F(TestFixture, Write�Ҷ�����־PASS) {
	EXPECT_CALL(mk, read)
		.WillRepeatedly(testing::Return(0xFF));

	dd.write(0xA, 'A');
}

TEST_F(TestFixture, Write�Ҷ���������ʾƼ�EXCEPTION) {
	EXPECT_CALL(mk, read, (0xA), ())
		.WillRepeatedly(testing::Return('B'));

	EXPECT_THROW({
		dd.write(0xA, 'A');
		}, WriteFailException);
}