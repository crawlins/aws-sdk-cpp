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
#include <aws/codepipeline/CodePipeline_EXPORTS.h>
#include <aws/codepipeline/CodePipelineRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/codepipeline/model/CurrentRevision.h>
#include <aws/codepipeline/model/ExecutionDetails.h>

namespace Aws
{
namespace CodePipeline
{
namespace Model
{

  /**
   * <p>Represents the input of a put job success result action. </p>
   */
  class AWS_CODEPIPELINE_API PutJobSuccessResultRequest : public CodePipelineRequest
  {
  public:
    PutJobSuccessResultRequest();
    Aws::String SerializePayload() const override;

    Aws::Http::HeaderValueCollection GetRequestSpecificHeaders() const override;

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline const Aws::String& GetJobId() const{ return m_jobId; }

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline void SetJobId(const Aws::String& value) { m_jobIdHasBeenSet = true; m_jobId = value; }

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline void SetJobId(Aws::String&& value) { m_jobIdHasBeenSet = true; m_jobId = value; }

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline void SetJobId(const char* value) { m_jobIdHasBeenSet = true; m_jobId.assign(value); }

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline PutJobSuccessResultRequest& WithJobId(const Aws::String& value) { SetJobId(value); return *this;}

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline PutJobSuccessResultRequest& WithJobId(Aws::String&& value) { SetJobId(value); return *this;}

    /**
     * <p>The unique system-generated ID of the job that succeeded. This is the same ID
     * returned from PollForJobs.</p>
     */
    inline PutJobSuccessResultRequest& WithJobId(const char* value) { SetJobId(value); return *this;}

    /**
     * <p>The ID of the current revision of the artifact successfully worked upon by
     * the job. </p>
     */
    inline const CurrentRevision& GetCurrentRevision() const{ return m_currentRevision; }

    /**
     * <p>The ID of the current revision of the artifact successfully worked upon by
     * the job. </p>
     */
    inline void SetCurrentRevision(const CurrentRevision& value) { m_currentRevisionHasBeenSet = true; m_currentRevision = value; }

    /**
     * <p>The ID of the current revision of the artifact successfully worked upon by
     * the job. </p>
     */
    inline void SetCurrentRevision(CurrentRevision&& value) { m_currentRevisionHasBeenSet = true; m_currentRevision = value; }

    /**
     * <p>The ID of the current revision of the artifact successfully worked upon by
     * the job. </p>
     */
    inline PutJobSuccessResultRequest& WithCurrentRevision(const CurrentRevision& value) { SetCurrentRevision(value); return *this;}

    /**
     * <p>The ID of the current revision of the artifact successfully worked upon by
     * the job. </p>
     */
    inline PutJobSuccessResultRequest& WithCurrentRevision(CurrentRevision&& value) { SetCurrentRevision(value); return *this;}

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline const Aws::String& GetContinuationToken() const{ return m_continuationToken; }

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline void SetContinuationToken(const Aws::String& value) { m_continuationTokenHasBeenSet = true; m_continuationToken = value; }

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline void SetContinuationToken(Aws::String&& value) { m_continuationTokenHasBeenSet = true; m_continuationToken = value; }

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline void SetContinuationToken(const char* value) { m_continuationTokenHasBeenSet = true; m_continuationToken.assign(value); }

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline PutJobSuccessResultRequest& WithContinuationToken(const Aws::String& value) { SetContinuationToken(value); return *this;}

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline PutJobSuccessResultRequest& WithContinuationToken(Aws::String&& value) { SetContinuationToken(value); return *this;}

    /**
     * <p>A system-generated token, such as a AWS CodeDeploy deployment ID, that the
     * successful job used to complete a job asynchronously. </p>
     */
    inline PutJobSuccessResultRequest& WithContinuationToken(const char* value) { SetContinuationToken(value); return *this;}

    /**
     * <p>The execution details of the successful job, such as the actions taken by the
     * job worker. </p>
     */
    inline const ExecutionDetails& GetExecutionDetails() const{ return m_executionDetails; }

    /**
     * <p>The execution details of the successful job, such as the actions taken by the
     * job worker. </p>
     */
    inline void SetExecutionDetails(const ExecutionDetails& value) { m_executionDetailsHasBeenSet = true; m_executionDetails = value; }

    /**
     * <p>The execution details of the successful job, such as the actions taken by the
     * job worker. </p>
     */
    inline void SetExecutionDetails(ExecutionDetails&& value) { m_executionDetailsHasBeenSet = true; m_executionDetails = value; }

    /**
     * <p>The execution details of the successful job, such as the actions taken by the
     * job worker. </p>
     */
    inline PutJobSuccessResultRequest& WithExecutionDetails(const ExecutionDetails& value) { SetExecutionDetails(value); return *this;}

    /**
     * <p>The execution details of the successful job, such as the actions taken by the
     * job worker. </p>
     */
    inline PutJobSuccessResultRequest& WithExecutionDetails(ExecutionDetails&& value) { SetExecutionDetails(value); return *this;}

  private:
    Aws::String m_jobId;
    bool m_jobIdHasBeenSet;
    CurrentRevision m_currentRevision;
    bool m_currentRevisionHasBeenSet;
    Aws::String m_continuationToken;
    bool m_continuationTokenHasBeenSet;
    ExecutionDetails m_executionDetails;
    bool m_executionDetailsHasBeenSet;
  };

} // namespace Model
} // namespace CodePipeline
} // namespace Aws
