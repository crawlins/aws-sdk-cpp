/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#pragma once
#include <aws/devicefarm/DeviceFarm_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/devicefarm/model/TestType.h>
#include <aws/devicefarm/model/DevicePlatform.h>
#include <aws/devicefarm/model/ExecutionStatus.h>
#include <aws/devicefarm/model/ExecutionResult.h>
#include <aws/devicefarm/model/Counters.h>
#include <aws/devicefarm/model/BillingMethod.h>
#include <aws/devicefarm/model/DeviceMinutes.h>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace DeviceFarm
{
namespace Model
{

  /**
   * <p>Represents an app on a set of devices with a specific test and
   * configuration.</p>
   */
  class AWS_DEVICEFARM_API Run
  {
  public:
    Run();
    Run(const Aws::Utils::Json::JsonValue& jsonValue);
    Run& operator=(const Aws::Utils::Json::JsonValue& jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;

    /**
     * <p>The run's ARN.</p>
     */
    inline const Aws::String& GetArn() const{ return m_arn; }

    /**
     * <p>The run's ARN.</p>
     */
    inline void SetArn(const Aws::String& value) { m_arnHasBeenSet = true; m_arn = value; }

    /**
     * <p>The run's ARN.</p>
     */
    inline void SetArn(Aws::String&& value) { m_arnHasBeenSet = true; m_arn = value; }

    /**
     * <p>The run's ARN.</p>
     */
    inline void SetArn(const char* value) { m_arnHasBeenSet = true; m_arn.assign(value); }

    /**
     * <p>The run's ARN.</p>
     */
    inline Run& WithArn(const Aws::String& value) { SetArn(value); return *this;}

    /**
     * <p>The run's ARN.</p>
     */
    inline Run& WithArn(Aws::String&& value) { SetArn(value); return *this;}

    /**
     * <p>The run's ARN.</p>
     */
    inline Run& WithArn(const char* value) { SetArn(value); return *this;}

    /**
     * <p>The run's name.</p>
     */
    inline const Aws::String& GetName() const{ return m_name; }

    /**
     * <p>The run's name.</p>
     */
    inline void SetName(const Aws::String& value) { m_nameHasBeenSet = true; m_name = value; }

    /**
     * <p>The run's name.</p>
     */
    inline void SetName(Aws::String&& value) { m_nameHasBeenSet = true; m_name = value; }

    /**
     * <p>The run's name.</p>
     */
    inline void SetName(const char* value) { m_nameHasBeenSet = true; m_name.assign(value); }

    /**
     * <p>The run's name.</p>
     */
    inline Run& WithName(const Aws::String& value) { SetName(value); return *this;}

    /**
     * <p>The run's name.</p>
     */
    inline Run& WithName(Aws::String&& value) { SetName(value); return *this;}

    /**
     * <p>The run's name.</p>
     */
    inline Run& WithName(const char* value) { SetName(value); return *this;}

    /**
     * <p>The run's type.</p> <p>Must be one of the following values:</p> <ul>
     * <li><p>BUILTIN_FUZZ: The built-in fuzz type.</p></li> <li><p>BUILTIN_EXPLORER:
     * For Android, an app explorer that will traverse an Android app, interacting with
     * it and capturing screenshots at the same time.</p></li>
     * <li><p>APPIUM_JAVA_JUNIT: The Appium Java JUnit type.</p></li>
     * <li><p>APPIUM_JAVA_TESTNG: The Appium Java TestNG type.</p></li>
     * <li><p>APPIUM_PYTHON: The Appium Python type.</p></li>
     * <li><p>APPIUM_WEB_JAVA_JUNIT: The Appium Java JUnit type for Web apps.</p></li>
     * <li><p>APPIUM_WEB_JAVA_TESTNG: The Appium Java TestNG type for Web
     * apps.</p></li> <li><p>APPIUM_WEB_PYTHON: The Appium Python type for Web
     * apps.</p></li> <li><p>CALABASH: The Calabash type.</p></li>
     * <li><p>INSTRUMENTATION: The Instrumentation type.</p></li> <li><p>UIAUTOMATION:
     * The uiautomation type.</p></li> <li><p>UIAUTOMATOR: The uiautomator
     * type.</p></li> <li><p>XCTEST: The XCode test type.</p></li> <li><p>XCTEST_UI:
     * The XCode UI test type.</p></li> </ul>
     */
    inline const TestType& GetType() const{ return m_type; }

    /**
     * <p>The run's type.</p> <p>Must be one of the following values:</p> <ul>
     * <li><p>BUILTIN_FUZZ: The built-in fuzz type.</p></li> <li><p>BUILTIN_EXPLORER:
     * For Android, an app explorer that will traverse an Android app, interacting with
     * it and capturing screenshots at the same time.</p></li>
     * <li><p>APPIUM_JAVA_JUNIT: The Appium Java JUnit type.</p></li>
     * <li><p>APPIUM_JAVA_TESTNG: The Appium Java TestNG type.</p></li>
     * <li><p>APPIUM_PYTHON: The Appium Python type.</p></li>
     * <li><p>APPIUM_WEB_JAVA_JUNIT: The Appium Java JUnit type for Web apps.</p></li>
     * <li><p>APPIUM_WEB_JAVA_TESTNG: The Appium Java TestNG type for Web
     * apps.</p></li> <li><p>APPIUM_WEB_PYTHON: The Appium Python type for Web
     * apps.</p></li> <li><p>CALABASH: The Calabash type.</p></li>
     * <li><p>INSTRUMENTATION: The Instrumentation type.</p></li> <li><p>UIAUTOMATION:
     * The uiautomation type.</p></li> <li><p>UIAUTOMATOR: The uiautomator
     * type.</p></li> <li><p>XCTEST: The XCode test type.</p></li> <li><p>XCTEST_UI:
     * The XCode UI test type.</p></li> </ul>
     */
    inline void SetType(const TestType& value) { m_typeHasBeenSet = true; m_type = value; }

    /**
     * <p>The run's type.</p> <p>Must be one of the following values:</p> <ul>
     * <li><p>BUILTIN_FUZZ: The built-in fuzz type.</p></li> <li><p>BUILTIN_EXPLORER:
     * For Android, an app explorer that will traverse an Android app, interacting with
     * it and capturing screenshots at the same time.</p></li>
     * <li><p>APPIUM_JAVA_JUNIT: The Appium Java JUnit type.</p></li>
     * <li><p>APPIUM_JAVA_TESTNG: The Appium Java TestNG type.</p></li>
     * <li><p>APPIUM_PYTHON: The Appium Python type.</p></li>
     * <li><p>APPIUM_WEB_JAVA_JUNIT: The Appium Java JUnit type for Web apps.</p></li>
     * <li><p>APPIUM_WEB_JAVA_TESTNG: The Appium Java TestNG type for Web
     * apps.</p></li> <li><p>APPIUM_WEB_PYTHON: The Appium Python type for Web
     * apps.</p></li> <li><p>CALABASH: The Calabash type.</p></li>
     * <li><p>INSTRUMENTATION: The Instrumentation type.</p></li> <li><p>UIAUTOMATION:
     * The uiautomation type.</p></li> <li><p>UIAUTOMATOR: The uiautomator
     * type.</p></li> <li><p>XCTEST: The XCode test type.</p></li> <li><p>XCTEST_UI:
     * The XCode UI test type.</p></li> </ul>
     */
    inline void SetType(TestType&& value) { m_typeHasBeenSet = true; m_type = value; }

    /**
     * <p>The run's type.</p> <p>Must be one of the following values:</p> <ul>
     * <li><p>BUILTIN_FUZZ: The built-in fuzz type.</p></li> <li><p>BUILTIN_EXPLORER:
     * For Android, an app explorer that will traverse an Android app, interacting with
     * it and capturing screenshots at the same time.</p></li>
     * <li><p>APPIUM_JAVA_JUNIT: The Appium Java JUnit type.</p></li>
     * <li><p>APPIUM_JAVA_TESTNG: The Appium Java TestNG type.</p></li>
     * <li><p>APPIUM_PYTHON: The Appium Python type.</p></li>
     * <li><p>APPIUM_WEB_JAVA_JUNIT: The Appium Java JUnit type for Web apps.</p></li>
     * <li><p>APPIUM_WEB_JAVA_TESTNG: The Appium Java TestNG type for Web
     * apps.</p></li> <li><p>APPIUM_WEB_PYTHON: The Appium Python type for Web
     * apps.</p></li> <li><p>CALABASH: The Calabash type.</p></li>
     * <li><p>INSTRUMENTATION: The Instrumentation type.</p></li> <li><p>UIAUTOMATION:
     * The uiautomation type.</p></li> <li><p>UIAUTOMATOR: The uiautomator
     * type.</p></li> <li><p>XCTEST: The XCode test type.</p></li> <li><p>XCTEST_UI:
     * The XCode UI test type.</p></li> </ul>
     */
    inline Run& WithType(const TestType& value) { SetType(value); return *this;}

    /**
     * <p>The run's type.</p> <p>Must be one of the following values:</p> <ul>
     * <li><p>BUILTIN_FUZZ: The built-in fuzz type.</p></li> <li><p>BUILTIN_EXPLORER:
     * For Android, an app explorer that will traverse an Android app, interacting with
     * it and capturing screenshots at the same time.</p></li>
     * <li><p>APPIUM_JAVA_JUNIT: The Appium Java JUnit type.</p></li>
     * <li><p>APPIUM_JAVA_TESTNG: The Appium Java TestNG type.</p></li>
     * <li><p>APPIUM_PYTHON: The Appium Python type.</p></li>
     * <li><p>APPIUM_WEB_JAVA_JUNIT: The Appium Java JUnit type for Web apps.</p></li>
     * <li><p>APPIUM_WEB_JAVA_TESTNG: The Appium Java TestNG type for Web
     * apps.</p></li> <li><p>APPIUM_WEB_PYTHON: The Appium Python type for Web
     * apps.</p></li> <li><p>CALABASH: The Calabash type.</p></li>
     * <li><p>INSTRUMENTATION: The Instrumentation type.</p></li> <li><p>UIAUTOMATION:
     * The uiautomation type.</p></li> <li><p>UIAUTOMATOR: The uiautomator
     * type.</p></li> <li><p>XCTEST: The XCode test type.</p></li> <li><p>XCTEST_UI:
     * The XCode UI test type.</p></li> </ul>
     */
    inline Run& WithType(TestType&& value) { SetType(value); return *this;}

    /**
     * <p>The run's platform.</p> <p>Allowed values include:</p> <ul> <li><p>ANDROID:
     * The Android platform.</p></li> <li><p>IOS: The iOS platform.</p></li> </ul>
     */
    inline const DevicePlatform& GetPlatform() const{ return m_platform; }

    /**
     * <p>The run's platform.</p> <p>Allowed values include:</p> <ul> <li><p>ANDROID:
     * The Android platform.</p></li> <li><p>IOS: The iOS platform.</p></li> </ul>
     */
    inline void SetPlatform(const DevicePlatform& value) { m_platformHasBeenSet = true; m_platform = value; }

    /**
     * <p>The run's platform.</p> <p>Allowed values include:</p> <ul> <li><p>ANDROID:
     * The Android platform.</p></li> <li><p>IOS: The iOS platform.</p></li> </ul>
     */
    inline void SetPlatform(DevicePlatform&& value) { m_platformHasBeenSet = true; m_platform = value; }

    /**
     * <p>The run's platform.</p> <p>Allowed values include:</p> <ul> <li><p>ANDROID:
     * The Android platform.</p></li> <li><p>IOS: The iOS platform.</p></li> </ul>
     */
    inline Run& WithPlatform(const DevicePlatform& value) { SetPlatform(value); return *this;}

    /**
     * <p>The run's platform.</p> <p>Allowed values include:</p> <ul> <li><p>ANDROID:
     * The Android platform.</p></li> <li><p>IOS: The iOS platform.</p></li> </ul>
     */
    inline Run& WithPlatform(DevicePlatform&& value) { SetPlatform(value); return *this;}

    /**
     * <p>When the run was created.</p>
     */
    inline double GetCreated() const{ return m_created; }

    /**
     * <p>When the run was created.</p>
     */
    inline void SetCreated(double value) { m_createdHasBeenSet = true; m_created = value; }

    /**
     * <p>When the run was created.</p>
     */
    inline Run& WithCreated(double value) { SetCreated(value); return *this;}

    /**
     * <p>The run's status.</p> <p>Allowed values include:</p> <ul> <li><p>COMPLETED: A
     * completed status.</p></li> <li><p>PENDING: A pending status.</p></li>
     * <li><p>PROCESSING: A processing status.</p></li> <li><p>RUNNING: A running
     * status.</p></li> <li><p>SCHEDULING: A scheduling status.</p></li> </ul>
     */
    inline const ExecutionStatus& GetStatus() const{ return m_status; }

    /**
     * <p>The run's status.</p> <p>Allowed values include:</p> <ul> <li><p>COMPLETED: A
     * completed status.</p></li> <li><p>PENDING: A pending status.</p></li>
     * <li><p>PROCESSING: A processing status.</p></li> <li><p>RUNNING: A running
     * status.</p></li> <li><p>SCHEDULING: A scheduling status.</p></li> </ul>
     */
    inline void SetStatus(const ExecutionStatus& value) { m_statusHasBeenSet = true; m_status = value; }

    /**
     * <p>The run's status.</p> <p>Allowed values include:</p> <ul> <li><p>COMPLETED: A
     * completed status.</p></li> <li><p>PENDING: A pending status.</p></li>
     * <li><p>PROCESSING: A processing status.</p></li> <li><p>RUNNING: A running
     * status.</p></li> <li><p>SCHEDULING: A scheduling status.</p></li> </ul>
     */
    inline void SetStatus(ExecutionStatus&& value) { m_statusHasBeenSet = true; m_status = value; }

    /**
     * <p>The run's status.</p> <p>Allowed values include:</p> <ul> <li><p>COMPLETED: A
     * completed status.</p></li> <li><p>PENDING: A pending status.</p></li>
     * <li><p>PROCESSING: A processing status.</p></li> <li><p>RUNNING: A running
     * status.</p></li> <li><p>SCHEDULING: A scheduling status.</p></li> </ul>
     */
    inline Run& WithStatus(const ExecutionStatus& value) { SetStatus(value); return *this;}

    /**
     * <p>The run's status.</p> <p>Allowed values include:</p> <ul> <li><p>COMPLETED: A
     * completed status.</p></li> <li><p>PENDING: A pending status.</p></li>
     * <li><p>PROCESSING: A processing status.</p></li> <li><p>RUNNING: A running
     * status.</p></li> <li><p>SCHEDULING: A scheduling status.</p></li> </ul>
     */
    inline Run& WithStatus(ExecutionStatus&& value) { SetStatus(value); return *this;}

    /**
     * <p>The run's result.</p> <p>Allowed values include:</p> <ul> <li><p>ERRORED: An
     * error condition.</p></li> <li><p>FAILED: A failed condition.</p></li>
     * <li><p>SKIPPED: A skipped condition.</p></li> <li><p>STOPPED: A stopped
     * condition.</p></li> <li><p>PASSED: A passing condition.</p></li> <li><p>PENDING:
     * A pending condition.</p></li> <li><p>WARNED: A warning condition.</p></li> </ul>
     */
    inline const ExecutionResult& GetResult() const{ return m_result; }

    /**
     * <p>The run's result.</p> <p>Allowed values include:</p> <ul> <li><p>ERRORED: An
     * error condition.</p></li> <li><p>FAILED: A failed condition.</p></li>
     * <li><p>SKIPPED: A skipped condition.</p></li> <li><p>STOPPED: A stopped
     * condition.</p></li> <li><p>PASSED: A passing condition.</p></li> <li><p>PENDING:
     * A pending condition.</p></li> <li><p>WARNED: A warning condition.</p></li> </ul>
     */
    inline void SetResult(const ExecutionResult& value) { m_resultHasBeenSet = true; m_result = value; }

    /**
     * <p>The run's result.</p> <p>Allowed values include:</p> <ul> <li><p>ERRORED: An
     * error condition.</p></li> <li><p>FAILED: A failed condition.</p></li>
     * <li><p>SKIPPED: A skipped condition.</p></li> <li><p>STOPPED: A stopped
     * condition.</p></li> <li><p>PASSED: A passing condition.</p></li> <li><p>PENDING:
     * A pending condition.</p></li> <li><p>WARNED: A warning condition.</p></li> </ul>
     */
    inline void SetResult(ExecutionResult&& value) { m_resultHasBeenSet = true; m_result = value; }

    /**
     * <p>The run's result.</p> <p>Allowed values include:</p> <ul> <li><p>ERRORED: An
     * error condition.</p></li> <li><p>FAILED: A failed condition.</p></li>
     * <li><p>SKIPPED: A skipped condition.</p></li> <li><p>STOPPED: A stopped
     * condition.</p></li> <li><p>PASSED: A passing condition.</p></li> <li><p>PENDING:
     * A pending condition.</p></li> <li><p>WARNED: A warning condition.</p></li> </ul>
     */
    inline Run& WithResult(const ExecutionResult& value) { SetResult(value); return *this;}

    /**
     * <p>The run's result.</p> <p>Allowed values include:</p> <ul> <li><p>ERRORED: An
     * error condition.</p></li> <li><p>FAILED: A failed condition.</p></li>
     * <li><p>SKIPPED: A skipped condition.</p></li> <li><p>STOPPED: A stopped
     * condition.</p></li> <li><p>PASSED: A passing condition.</p></li> <li><p>PENDING:
     * A pending condition.</p></li> <li><p>WARNED: A warning condition.</p></li> </ul>
     */
    inline Run& WithResult(ExecutionResult&& value) { SetResult(value); return *this;}

    /**
     * <p>The run's start time.</p>
     */
    inline double GetStarted() const{ return m_started; }

    /**
     * <p>The run's start time.</p>
     */
    inline void SetStarted(double value) { m_startedHasBeenSet = true; m_started = value; }

    /**
     * <p>The run's start time.</p>
     */
    inline Run& WithStarted(double value) { SetStarted(value); return *this;}

    /**
     * <p>The run's stop time.</p>
     */
    inline double GetStopped() const{ return m_stopped; }

    /**
     * <p>The run's stop time.</p>
     */
    inline void SetStopped(double value) { m_stoppedHasBeenSet = true; m_stopped = value; }

    /**
     * <p>The run's stop time.</p>
     */
    inline Run& WithStopped(double value) { SetStopped(value); return *this;}

    /**
     * <p>The run's result counters.</p>
     */
    inline const Counters& GetCounters() const{ return m_counters; }

    /**
     * <p>The run's result counters.</p>
     */
    inline void SetCounters(const Counters& value) { m_countersHasBeenSet = true; m_counters = value; }

    /**
     * <p>The run's result counters.</p>
     */
    inline void SetCounters(Counters&& value) { m_countersHasBeenSet = true; m_counters = value; }

    /**
     * <p>The run's result counters.</p>
     */
    inline Run& WithCounters(const Counters& value) { SetCounters(value); return *this;}

    /**
     * <p>The run's result counters.</p>
     */
    inline Run& WithCounters(Counters&& value) { SetCounters(value); return *this;}

    /**
     * <p>A message about the run's result.</p>
     */
    inline const Aws::String& GetMessage() const{ return m_message; }

    /**
     * <p>A message about the run's result.</p>
     */
    inline void SetMessage(const Aws::String& value) { m_messageHasBeenSet = true; m_message = value; }

    /**
     * <p>A message about the run's result.</p>
     */
    inline void SetMessage(Aws::String&& value) { m_messageHasBeenSet = true; m_message = value; }

    /**
     * <p>A message about the run's result.</p>
     */
    inline void SetMessage(const char* value) { m_messageHasBeenSet = true; m_message.assign(value); }

    /**
     * <p>A message about the run's result.</p>
     */
    inline Run& WithMessage(const Aws::String& value) { SetMessage(value); return *this;}

    /**
     * <p>A message about the run's result.</p>
     */
    inline Run& WithMessage(Aws::String&& value) { SetMessage(value); return *this;}

    /**
     * <p>A message about the run's result.</p>
     */
    inline Run& WithMessage(const char* value) { SetMessage(value); return *this;}

    /**
     * <p>The total number of jobs for the run.</p>
     */
    inline long GetTotalJobs() const{ return m_totalJobs; }

    /**
     * <p>The total number of jobs for the run.</p>
     */
    inline void SetTotalJobs(long value) { m_totalJobsHasBeenSet = true; m_totalJobs = value; }

    /**
     * <p>The total number of jobs for the run.</p>
     */
    inline Run& WithTotalJobs(long value) { SetTotalJobs(value); return *this;}

    /**
     * <p>The total number of completed jobs.</p>
     */
    inline long GetCompletedJobs() const{ return m_completedJobs; }

    /**
     * <p>The total number of completed jobs.</p>
     */
    inline void SetCompletedJobs(long value) { m_completedJobsHasBeenSet = true; m_completedJobs = value; }

    /**
     * <p>The total number of completed jobs.</p>
     */
    inline Run& WithCompletedJobs(long value) { SetCompletedJobs(value); return *this;}

    /**
     * <p>Specifies the billing method for a test run: <code>metered</code> or
     * <code>unmetered</code>. If the parameter is not specified, the default value is
     * <code>unmetered</code>.</p>
     */
    inline const BillingMethod& GetBillingMethod() const{ return m_billingMethod; }

    /**
     * <p>Specifies the billing method for a test run: <code>metered</code> or
     * <code>unmetered</code>. If the parameter is not specified, the default value is
     * <code>unmetered</code>.</p>
     */
    inline void SetBillingMethod(const BillingMethod& value) { m_billingMethodHasBeenSet = true; m_billingMethod = value; }

    /**
     * <p>Specifies the billing method for a test run: <code>metered</code> or
     * <code>unmetered</code>. If the parameter is not specified, the default value is
     * <code>unmetered</code>.</p>
     */
    inline void SetBillingMethod(BillingMethod&& value) { m_billingMethodHasBeenSet = true; m_billingMethod = value; }

    /**
     * <p>Specifies the billing method for a test run: <code>metered</code> or
     * <code>unmetered</code>. If the parameter is not specified, the default value is
     * <code>unmetered</code>.</p>
     */
    inline Run& WithBillingMethod(const BillingMethod& value) { SetBillingMethod(value); return *this;}

    /**
     * <p>Specifies the billing method for a test run: <code>metered</code> or
     * <code>unmetered</code>. If the parameter is not specified, the default value is
     * <code>unmetered</code>.</p>
     */
    inline Run& WithBillingMethod(BillingMethod&& value) { SetBillingMethod(value); return *this;}

    /**
     * <p>Represents the total (metered or unmetered) minutes used by the test run.</p>
     */
    inline const DeviceMinutes& GetDeviceMinutes() const{ return m_deviceMinutes; }

    /**
     * <p>Represents the total (metered or unmetered) minutes used by the test run.</p>
     */
    inline void SetDeviceMinutes(const DeviceMinutes& value) { m_deviceMinutesHasBeenSet = true; m_deviceMinutes = value; }

    /**
     * <p>Represents the total (metered or unmetered) minutes used by the test run.</p>
     */
    inline void SetDeviceMinutes(DeviceMinutes&& value) { m_deviceMinutesHasBeenSet = true; m_deviceMinutes = value; }

    /**
     * <p>Represents the total (metered or unmetered) minutes used by the test run.</p>
     */
    inline Run& WithDeviceMinutes(const DeviceMinutes& value) { SetDeviceMinutes(value); return *this;}

    /**
     * <p>Represents the total (metered or unmetered) minutes used by the test run.</p>
     */
    inline Run& WithDeviceMinutes(DeviceMinutes&& value) { SetDeviceMinutes(value); return *this;}

  private:
    Aws::String m_arn;
    bool m_arnHasBeenSet;
    Aws::String m_name;
    bool m_nameHasBeenSet;
    TestType m_type;
    bool m_typeHasBeenSet;
    DevicePlatform m_platform;
    bool m_platformHasBeenSet;
    double m_created;
    bool m_createdHasBeenSet;
    ExecutionStatus m_status;
    bool m_statusHasBeenSet;
    ExecutionResult m_result;
    bool m_resultHasBeenSet;
    double m_started;
    bool m_startedHasBeenSet;
    double m_stopped;
    bool m_stoppedHasBeenSet;
    Counters m_counters;
    bool m_countersHasBeenSet;
    Aws::String m_message;
    bool m_messageHasBeenSet;
    long m_totalJobs;
    bool m_totalJobsHasBeenSet;
    long m_completedJobs;
    bool m_completedJobsHasBeenSet;
    BillingMethod m_billingMethod;
    bool m_billingMethodHasBeenSet;
    DeviceMinutes m_deviceMinutes;
    bool m_deviceMinutesHasBeenSet;
  };

} // namespace Model
} // namespace DeviceFarm
} // namespace Aws
