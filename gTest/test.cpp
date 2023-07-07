#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project1/DeviceDriver.cpp"
#include "../Project1/Application.cpp"

using namespace testing;

//class DeviceDriverFixture : public testing::Test
//{
//public:
//	DeviceDriver driver;
//};

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, flashReadSuccess) {
	FlashMock flashMock;

	long addr = 0;
	int expectResult = 'A';

	EXPECT_CALL(flashMock, read(addr)).Times(DeviceDriver::ReadTryCount).WillRepeatedly(Return(expectResult));

	DeviceDriver driver(&flashMock);

	EXPECT_THAT(driver.read(addr), Eq(expectResult));
}

TEST(TestCaseName, flashReadFailSimple) {
	FlashMock flashMock;

	long addr = 1;
	int expectResult = 'A';
	int failResult = 'Z';

	EXPECT_CALL(flashMock, read(addr)).WillOnce(Return(failResult)).WillRepeatedly(Return(expectResult));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST(TestCaseName, flashReadFailAt2ndTry) {
	FlashMock flashMock;

	long addr = 10;
	int expectResult = 'A';
	int failResult = 'Z';

	EXPECT_CALL(flashMock, read(addr)).Times(2).WillOnce(Return('A')).WillOnce(Return('Z'));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST(TestCaseName, flashReadFailAt3rdTry) {
	FlashMock flashMock;

	long addr = 10;
	int expectResult = 'A';
	int failResult = 'Z';

	EXPECT_CALL(flashMock, read(addr)).Times(3).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('Z'));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST(TestCaseName, flashReadFailAt4thTry) {
	FlashMock flashMock;

	long addr = 10;
	int expectResult = 'A';
	int failResult = 'Z';

	EXPECT_CALL(flashMock, read(addr)).Times(4).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('Z'));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST(TestCaseName, flashReadFailAt5thTry) {
	FlashMock flashMock;

	long addr = 10;
	int expectResult = 'A';
	int failResult = 'Z';

	EXPECT_CALL(flashMock, read(addr)).Times(5).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('Z'));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(addr), ReadFailException);
}

TEST(TestCaseName, flashWriteSuccess) {
	FlashMock flashMock;

	long addr = 10;
	int data = 'A';

	EXPECT_CALL(flashMock, read(addr)).Times(1).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return('A')).WillOnce(Return(DeviceDriver::CleanPattern));
	EXPECT_CALL(flashMock, write(addr, data)).Times(1);

	DeviceDriver driver(&flashMock);

	driver.write(addr, data);
}

TEST(TestCaseName, flashWriteFail) {
	FlashMock flashMock;

	long addr = 10;
	int data = 'A';

	EXPECT_CALL(flashMock, read(addr)).Times(1).WillOnce(Return(DeviceDriver::CleanPattern));
	EXPECT_CALL(flashMock, write(addr, data)).Times(0);

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.write(addr, data), WriteFailException);
}

TEST(TestCaseName, flashReadAndPrint) {
	FlashMock flashMock;

	int addrStart = 10;
	int addrEnd = 20;
	int data = 'A';

	for(int addr = addrStart; addr <= addrEnd; addr++)
	{
		EXPECT_CALL(flashMock, read(addr)).Times(DeviceDriver::ReadTryCount).WillRepeatedly(Return(data));		
	}

	DeviceDriver driver(&flashMock);
	Application app(&driver);

	app.ReadAndPrint(addrStart, addrEnd);
}