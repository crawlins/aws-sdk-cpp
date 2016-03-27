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
#include <aws/core/utils/Outcome.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/EC2Endpoint.h>
#include <aws/ec2/EC2ErrorMarshaller.h>
#include <aws/ec2/model/AcceptVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/AllocateAddressRequest.h>
#include <aws/ec2/model/AllocateHostsRequest.h>
#include <aws/ec2/model/AssignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/AssociateAddressRequest.h>
#include <aws/ec2/model/AssociateDhcpOptionsRequest.h>
#include <aws/ec2/model/AssociateRouteTableRequest.h>
#include <aws/ec2/model/AttachClassicLinkVpcRequest.h>
#include <aws/ec2/model/AttachInternetGatewayRequest.h>
#include <aws/ec2/model/AttachNetworkInterfaceRequest.h>
#include <aws/ec2/model/AttachVolumeRequest.h>
#include <aws/ec2/model/AttachVpnGatewayRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/BundleInstanceRequest.h>
#include <aws/ec2/model/CancelBundleTaskRequest.h>
#include <aws/ec2/model/CancelConversionTaskRequest.h>
#include <aws/ec2/model/CancelExportTaskRequest.h>
#include <aws/ec2/model/CancelImportTaskRequest.h>
#include <aws/ec2/model/CancelReservedInstancesListingRequest.h>
#include <aws/ec2/model/CancelSpotFleetRequestsRequest.h>
#include <aws/ec2/model/CancelSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/ConfirmProductInstanceRequest.h>
#include <aws/ec2/model/CopyImageRequest.h>
#include <aws/ec2/model/CopySnapshotRequest.h>
#include <aws/ec2/model/CreateCustomerGatewayRequest.h>
#include <aws/ec2/model/CreateDhcpOptionsRequest.h>
#include <aws/ec2/model/CreateFlowLogsRequest.h>
#include <aws/ec2/model/CreateImageRequest.h>
#include <aws/ec2/model/CreateInstanceExportTaskRequest.h>
#include <aws/ec2/model/CreateInternetGatewayRequest.h>
#include <aws/ec2/model/CreateKeyPairRequest.h>
#include <aws/ec2/model/CreateNatGatewayRequest.h>
#include <aws/ec2/model/CreateNetworkAclRequest.h>
#include <aws/ec2/model/CreateNetworkAclEntryRequest.h>
#include <aws/ec2/model/CreateNetworkInterfaceRequest.h>
#include <aws/ec2/model/CreatePlacementGroupRequest.h>
#include <aws/ec2/model/CreateReservedInstancesListingRequest.h>
#include <aws/ec2/model/CreateRouteRequest.h>
#include <aws/ec2/model/CreateRouteTableRequest.h>
#include <aws/ec2/model/CreateSecurityGroupRequest.h>
#include <aws/ec2/model/CreateSnapshotRequest.h>
#include <aws/ec2/model/CreateSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/CreateSubnetRequest.h>
#include <aws/ec2/model/CreateTagsRequest.h>
#include <aws/ec2/model/CreateVolumeRequest.h>
#include <aws/ec2/model/CreateVpcRequest.h>
#include <aws/ec2/model/CreateVpcEndpointRequest.h>
#include <aws/ec2/model/CreateVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRouteRequest.h>
#include <aws/ec2/model/CreateVpnGatewayRequest.h>
#include <aws/ec2/model/DeleteCustomerGatewayRequest.h>
#include <aws/ec2/model/DeleteDhcpOptionsRequest.h>
#include <aws/ec2/model/DeleteFlowLogsRequest.h>
#include <aws/ec2/model/DeleteInternetGatewayRequest.h>
#include <aws/ec2/model/DeleteKeyPairRequest.h>
#include <aws/ec2/model/DeleteNatGatewayRequest.h>
#include <aws/ec2/model/DeleteNetworkAclRequest.h>
#include <aws/ec2/model/DeleteNetworkAclEntryRequest.h>
#include <aws/ec2/model/DeleteNetworkInterfaceRequest.h>
#include <aws/ec2/model/DeletePlacementGroupRequest.h>
#include <aws/ec2/model/DeleteRouteRequest.h>
#include <aws/ec2/model/DeleteRouteTableRequest.h>
#include <aws/ec2/model/DeleteSecurityGroupRequest.h>
#include <aws/ec2/model/DeleteSnapshotRequest.h>
#include <aws/ec2/model/DeleteSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DeleteSubnetRequest.h>
#include <aws/ec2/model/DeleteTagsRequest.h>
#include <aws/ec2/model/DeleteVolumeRequest.h>
#include <aws/ec2/model/DeleteVpcRequest.h>
#include <aws/ec2/model/DeleteVpcEndpointsRequest.h>
#include <aws/ec2/model/DeleteVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRouteRequest.h>
#include <aws/ec2/model/DeleteVpnGatewayRequest.h>
#include <aws/ec2/model/DeregisterImageRequest.h>
#include <aws/ec2/model/DescribeAccountAttributesRequest.h>
#include <aws/ec2/model/DescribeAddressesRequest.h>
#include <aws/ec2/model/DescribeAvailabilityZonesRequest.h>
#include <aws/ec2/model/DescribeBundleTasksRequest.h>
#include <aws/ec2/model/DescribeClassicLinkInstancesRequest.h>
#include <aws/ec2/model/DescribeConversionTasksRequest.h>
#include <aws/ec2/model/DescribeCustomerGatewaysRequest.h>
#include <aws/ec2/model/DescribeDhcpOptionsRequest.h>
#include <aws/ec2/model/DescribeExportTasksRequest.h>
#include <aws/ec2/model/DescribeFlowLogsRequest.h>
#include <aws/ec2/model/DescribeHostsRequest.h>
#include <aws/ec2/model/DescribeIdFormatRequest.h>
#include <aws/ec2/model/DescribeImageAttributeRequest.h>
#include <aws/ec2/model/DescribeImagesRequest.h>
#include <aws/ec2/model/DescribeImportImageTasksRequest.h>
#include <aws/ec2/model/DescribeImportSnapshotTasksRequest.h>
#include <aws/ec2/model/DescribeInstanceAttributeRequest.h>
#include <aws/ec2/model/DescribeInstanceStatusRequest.h>
#include <aws/ec2/model/DescribeInstancesRequest.h>
#include <aws/ec2/model/DescribeInternetGatewaysRequest.h>
#include <aws/ec2/model/DescribeKeyPairsRequest.h>
#include <aws/ec2/model/DescribeMovingAddressesRequest.h>
#include <aws/ec2/model/DescribeNatGatewaysRequest.h>
#include <aws/ec2/model/DescribeNetworkAclsRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfacesRequest.h>
#include <aws/ec2/model/DescribePlacementGroupsRequest.h>
#include <aws/ec2/model/DescribePrefixListsRequest.h>
#include <aws/ec2/model/DescribeRegionsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesListingsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesModificationsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesOfferingsRequest.h>
#include <aws/ec2/model/DescribeRouteTablesRequest.h>
#include <aws/ec2/model/DescribeScheduledInstanceAvailabilityRequest.h>
#include <aws/ec2/model/DescribeScheduledInstancesRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupsRequest.h>
#include <aws/ec2/model/DescribeSnapshotAttributeRequest.h>
#include <aws/ec2/model/DescribeSnapshotsRequest.h>
#include <aws/ec2/model/DescribeSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DescribeSpotFleetInstancesRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestHistoryRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotPriceHistoryRequest.h>
#include <aws/ec2/model/DescribeSubnetsRequest.h>
#include <aws/ec2/model/DescribeTagsRequest.h>
#include <aws/ec2/model/DescribeVolumeAttributeRequest.h>
#include <aws/ec2/model/DescribeVolumeStatusRequest.h>
#include <aws/ec2/model/DescribeVolumesRequest.h>
#include <aws/ec2/model/DescribeVpcAttributeRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointServicesRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointsRequest.h>
#include <aws/ec2/model/DescribeVpcPeeringConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpcsRequest.h>
#include <aws/ec2/model/DescribeVpnConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpnGatewaysRequest.h>
#include <aws/ec2/model/DetachClassicLinkVpcRequest.h>
#include <aws/ec2/model/DetachInternetGatewayRequest.h>
#include <aws/ec2/model/DetachNetworkInterfaceRequest.h>
#include <aws/ec2/model/DetachVolumeRequest.h>
#include <aws/ec2/model/DetachVpnGatewayRequest.h>
#include <aws/ec2/model/DisableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DisassociateAddressRequest.h>
#include <aws/ec2/model/DisassociateRouteTableRequest.h>
#include <aws/ec2/model/EnableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/EnableVolumeIORequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkRequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/GetConsoleOutputRequest.h>
#include <aws/ec2/model/GetPasswordDataRequest.h>
#include <aws/ec2/model/ImportImageRequest.h>
#include <aws/ec2/model/ImportInstanceRequest.h>
#include <aws/ec2/model/ImportKeyPairRequest.h>
#include <aws/ec2/model/ImportSnapshotRequest.h>
#include <aws/ec2/model/ImportVolumeRequest.h>
#include <aws/ec2/model/ModifyHostsRequest.h>
#include <aws/ec2/model/ModifyIdFormatRequest.h>
#include <aws/ec2/model/ModifyImageAttributeRequest.h>
#include <aws/ec2/model/ModifyInstanceAttributeRequest.h>
#include <aws/ec2/model/ModifyInstancePlacementRequest.h>
#include <aws/ec2/model/ModifyNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ModifyReservedInstancesRequest.h>
#include <aws/ec2/model/ModifySnapshotAttributeRequest.h>
#include <aws/ec2/model/ModifySpotFleetRequestRequest.h>
#include <aws/ec2/model/ModifySubnetAttributeRequest.h>
#include <aws/ec2/model/ModifyVolumeAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointRequest.h>
#include <aws/ec2/model/MonitorInstancesRequest.h>
#include <aws/ec2/model/MoveAddressToVpcRequest.h>
#include <aws/ec2/model/PurchaseReservedInstancesOfferingRequest.h>
#include <aws/ec2/model/PurchaseScheduledInstancesRequest.h>
#include <aws/ec2/model/RebootInstancesRequest.h>
#include <aws/ec2/model/RegisterImageRequest.h>
#include <aws/ec2/model/RejectVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/ReleaseAddressRequest.h>
#include <aws/ec2/model/ReleaseHostsRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclAssociationRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclEntryRequest.h>
#include <aws/ec2/model/ReplaceRouteRequest.h>
#include <aws/ec2/model/ReplaceRouteTableAssociationRequest.h>
#include <aws/ec2/model/ReportInstanceStatusRequest.h>
#include <aws/ec2/model/RequestSpotFleetRequest.h>
#include <aws/ec2/model/RequestSpotInstancesRequest.h>
#include <aws/ec2/model/ResetImageAttributeRequest.h>
#include <aws/ec2/model/ResetInstanceAttributeRequest.h>
#include <aws/ec2/model/ResetNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ResetSnapshotAttributeRequest.h>
#include <aws/ec2/model/RestoreAddressToClassicRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/RunInstancesRequest.h>
#include <aws/ec2/model/RunScheduledInstancesRequest.h>
#include <aws/ec2/model/StartInstancesRequest.h>
#include <aws/ec2/model/StopInstancesRequest.h>
#include <aws/ec2/model/TerminateInstancesRequest.h>
#include <aws/ec2/model/UnassignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/UnmonitorInstancesRequest.h>

using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::EC2;
using namespace Aws::EC2::Model;
using namespace Aws::Http;
using namespace Aws::Utils::Xml;


CopyImageOutcome EC2Client::CopyImage(const CopyImageRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CopyImageOutcome(CopyImageResponse(outcome.GetResult()));
  }
  else
  {
    return CopyImageOutcome(outcome.GetError());
  }
}

CopyImageOutcomeCallable EC2Client::CopyImageCallable(const CopyImageRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CopyImage, this, request);
}

void EC2Client::CopyImageAsync(const CopyImageRequest& request, const CopyImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CopyImageAsyncHelper, this, request, handler, context);
}

void EC2Client::CopyImageAsyncHelper(const CopyImageRequest& request, const CopyImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CopyImage(request), context);
}

CopySnapshotOutcome EC2Client::CopySnapshot(const CopySnapshotRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CopySnapshotOutcome(CopySnapshotResponse(outcome.GetResult()));
  }
  else
  {
    return CopySnapshotOutcome(outcome.GetError());
  }
}

CopySnapshotOutcomeCallable EC2Client::CopySnapshotCallable(const CopySnapshotRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CopySnapshot, this, request);
}

void EC2Client::CopySnapshotAsync(const CopySnapshotRequest& request, const CopySnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CopySnapshotAsyncHelper, this, request, handler, context);
}

void EC2Client::CopySnapshotAsyncHelper(const CopySnapshotRequest& request, const CopySnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CopySnapshot(request), context);
}

CreateCustomerGatewayOutcome EC2Client::CreateCustomerGateway(const CreateCustomerGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateCustomerGatewayOutcome(CreateCustomerGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return CreateCustomerGatewayOutcome(outcome.GetError());
  }
}

CreateCustomerGatewayOutcomeCallable EC2Client::CreateCustomerGatewayCallable(const CreateCustomerGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateCustomerGateway, this, request);
}

void EC2Client::CreateCustomerGatewayAsync(const CreateCustomerGatewayRequest& request, const CreateCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateCustomerGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateCustomerGatewayAsyncHelper(const CreateCustomerGatewayRequest& request, const CreateCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateCustomerGateway(request), context);
}

CreateDhcpOptionsOutcome EC2Client::CreateDhcpOptions(const CreateDhcpOptionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateDhcpOptionsOutcome(CreateDhcpOptionsResponse(outcome.GetResult()));
  }
  else
  {
    return CreateDhcpOptionsOutcome(outcome.GetError());
  }
}

CreateDhcpOptionsOutcomeCallable EC2Client::CreateDhcpOptionsCallable(const CreateDhcpOptionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateDhcpOptions, this, request);
}

void EC2Client::CreateDhcpOptionsAsync(const CreateDhcpOptionsRequest& request, const CreateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateDhcpOptionsAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateDhcpOptionsAsyncHelper(const CreateDhcpOptionsRequest& request, const CreateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateDhcpOptions(request), context);
}

CreateFlowLogsOutcome EC2Client::CreateFlowLogs(const CreateFlowLogsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateFlowLogsOutcome(CreateFlowLogsResponse(outcome.GetResult()));
  }
  else
  {
    return CreateFlowLogsOutcome(outcome.GetError());
  }
}

CreateFlowLogsOutcomeCallable EC2Client::CreateFlowLogsCallable(const CreateFlowLogsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateFlowLogs, this, request);
}

void EC2Client::CreateFlowLogsAsync(const CreateFlowLogsRequest& request, const CreateFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateFlowLogsAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateFlowLogsAsyncHelper(const CreateFlowLogsRequest& request, const CreateFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateFlowLogs(request), context);
}

CreateImageOutcome EC2Client::CreateImage(const CreateImageRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateImageOutcome(CreateImageResponse(outcome.GetResult()));
  }
  else
  {
    return CreateImageOutcome(outcome.GetError());
  }
}

CreateImageOutcomeCallable EC2Client::CreateImageCallable(const CreateImageRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateImage, this, request);
}

void EC2Client::CreateImageAsync(const CreateImageRequest& request, const CreateImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateImageAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateImageAsyncHelper(const CreateImageRequest& request, const CreateImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateImage(request), context);
}

CreateInstanceExportTaskOutcome EC2Client::CreateInstanceExportTask(const CreateInstanceExportTaskRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateInstanceExportTaskOutcome(CreateInstanceExportTaskResponse(outcome.GetResult()));
  }
  else
  {
    return CreateInstanceExportTaskOutcome(outcome.GetError());
  }
}

CreateInstanceExportTaskOutcomeCallable EC2Client::CreateInstanceExportTaskCallable(const CreateInstanceExportTaskRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateInstanceExportTask, this, request);
}

void EC2Client::CreateInstanceExportTaskAsync(const CreateInstanceExportTaskRequest& request, const CreateInstanceExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateInstanceExportTaskAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateInstanceExportTaskAsyncHelper(const CreateInstanceExportTaskRequest& request, const CreateInstanceExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateInstanceExportTask(request), context);
}

CreateInternetGatewayOutcome EC2Client::CreateInternetGateway(const CreateInternetGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateInternetGatewayOutcome(CreateInternetGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return CreateInternetGatewayOutcome(outcome.GetError());
  }
}

CreateInternetGatewayOutcomeCallable EC2Client::CreateInternetGatewayCallable(const CreateInternetGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateInternetGateway, this, request);
}

void EC2Client::CreateInternetGatewayAsync(const CreateInternetGatewayRequest& request, const CreateInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateInternetGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateInternetGatewayAsyncHelper(const CreateInternetGatewayRequest& request, const CreateInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateInternetGateway(request), context);
}

CreateKeyPairOutcome EC2Client::CreateKeyPair(const CreateKeyPairRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateKeyPairOutcome(CreateKeyPairResponse(outcome.GetResult()));
  }
  else
  {
    return CreateKeyPairOutcome(outcome.GetError());
  }
}

CreateKeyPairOutcomeCallable EC2Client::CreateKeyPairCallable(const CreateKeyPairRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateKeyPair, this, request);
}

void EC2Client::CreateKeyPairAsync(const CreateKeyPairRequest& request, const CreateKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateKeyPairAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateKeyPairAsyncHelper(const CreateKeyPairRequest& request, const CreateKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateKeyPair(request), context);
}

CreateNatGatewayOutcome EC2Client::CreateNatGateway(const CreateNatGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateNatGatewayOutcome(CreateNatGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return CreateNatGatewayOutcome(outcome.GetError());
  }
}

CreateNatGatewayOutcomeCallable EC2Client::CreateNatGatewayCallable(const CreateNatGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateNatGateway, this, request);
}

void EC2Client::CreateNatGatewayAsync(const CreateNatGatewayRequest& request, const CreateNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateNatGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateNatGatewayAsyncHelper(const CreateNatGatewayRequest& request, const CreateNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateNatGateway(request), context);
}

CreateNetworkAclOutcome EC2Client::CreateNetworkAcl(const CreateNetworkAclRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateNetworkAclOutcome(CreateNetworkAclResponse(outcome.GetResult()));
  }
  else
  {
    return CreateNetworkAclOutcome(outcome.GetError());
  }
}

CreateNetworkAclOutcomeCallable EC2Client::CreateNetworkAclCallable(const CreateNetworkAclRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateNetworkAcl, this, request);
}

void EC2Client::CreateNetworkAclAsync(const CreateNetworkAclRequest& request, const CreateNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateNetworkAclAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateNetworkAclAsyncHelper(const CreateNetworkAclRequest& request, const CreateNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateNetworkAcl(request), context);
}

CreateNetworkAclEntryOutcome EC2Client::CreateNetworkAclEntry(const CreateNetworkAclEntryRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateNetworkAclEntryOutcome(NoResult());
  }
  else
  {
    return CreateNetworkAclEntryOutcome(outcome.GetError());
  }
}

CreateNetworkAclEntryOutcomeCallable EC2Client::CreateNetworkAclEntryCallable(const CreateNetworkAclEntryRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateNetworkAclEntry, this, request);
}

void EC2Client::CreateNetworkAclEntryAsync(const CreateNetworkAclEntryRequest& request, const CreateNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateNetworkAclEntryAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateNetworkAclEntryAsyncHelper(const CreateNetworkAclEntryRequest& request, const CreateNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateNetworkAclEntry(request), context);
}

CreateNetworkInterfaceOutcome EC2Client::CreateNetworkInterface(const CreateNetworkInterfaceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateNetworkInterfaceOutcome(CreateNetworkInterfaceResponse(outcome.GetResult()));
  }
  else
  {
    return CreateNetworkInterfaceOutcome(outcome.GetError());
  }
}

CreateNetworkInterfaceOutcomeCallable EC2Client::CreateNetworkInterfaceCallable(const CreateNetworkInterfaceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateNetworkInterface, this, request);
}

void EC2Client::CreateNetworkInterfaceAsync(const CreateNetworkInterfaceRequest& request, const CreateNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateNetworkInterfaceAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateNetworkInterfaceAsyncHelper(const CreateNetworkInterfaceRequest& request, const CreateNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateNetworkInterface(request), context);
}

CreatePlacementGroupOutcome EC2Client::CreatePlacementGroup(const CreatePlacementGroupRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreatePlacementGroupOutcome(NoResult());
  }
  else
  {
    return CreatePlacementGroupOutcome(outcome.GetError());
  }
}

CreatePlacementGroupOutcomeCallable EC2Client::CreatePlacementGroupCallable(const CreatePlacementGroupRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreatePlacementGroup, this, request);
}

void EC2Client::CreatePlacementGroupAsync(const CreatePlacementGroupRequest& request, const CreatePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreatePlacementGroupAsyncHelper, this, request, handler, context);
}

void EC2Client::CreatePlacementGroupAsyncHelper(const CreatePlacementGroupRequest& request, const CreatePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreatePlacementGroup(request), context);
}

CreateReservedInstancesListingOutcome EC2Client::CreateReservedInstancesListing(const CreateReservedInstancesListingRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateReservedInstancesListingOutcome(CreateReservedInstancesListingResponse(outcome.GetResult()));
  }
  else
  {
    return CreateReservedInstancesListingOutcome(outcome.GetError());
  }
}

CreateReservedInstancesListingOutcomeCallable EC2Client::CreateReservedInstancesListingCallable(const CreateReservedInstancesListingRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateReservedInstancesListing, this, request);
}

void EC2Client::CreateReservedInstancesListingAsync(const CreateReservedInstancesListingRequest& request, const CreateReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateReservedInstancesListingAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateReservedInstancesListingAsyncHelper(const CreateReservedInstancesListingRequest& request, const CreateReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateReservedInstancesListing(request), context);
}

CreateRouteOutcome EC2Client::CreateRoute(const CreateRouteRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateRouteOutcome(CreateRouteResponse(outcome.GetResult()));
  }
  else
  {
    return CreateRouteOutcome(outcome.GetError());
  }
}

CreateRouteOutcomeCallable EC2Client::CreateRouteCallable(const CreateRouteRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateRoute, this, request);
}

void EC2Client::CreateRouteAsync(const CreateRouteRequest& request, const CreateRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateRouteAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateRouteAsyncHelper(const CreateRouteRequest& request, const CreateRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateRoute(request), context);
}

CreateRouteTableOutcome EC2Client::CreateRouteTable(const CreateRouteTableRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateRouteTableOutcome(CreateRouteTableResponse(outcome.GetResult()));
  }
  else
  {
    return CreateRouteTableOutcome(outcome.GetError());
  }
}

CreateRouteTableOutcomeCallable EC2Client::CreateRouteTableCallable(const CreateRouteTableRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateRouteTable, this, request);
}

void EC2Client::CreateRouteTableAsync(const CreateRouteTableRequest& request, const CreateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateRouteTableAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateRouteTableAsyncHelper(const CreateRouteTableRequest& request, const CreateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateRouteTable(request), context);
}

CreateSecurityGroupOutcome EC2Client::CreateSecurityGroup(const CreateSecurityGroupRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateSecurityGroupOutcome(CreateSecurityGroupResponse(outcome.GetResult()));
  }
  else
  {
    return CreateSecurityGroupOutcome(outcome.GetError());
  }
}

CreateSecurityGroupOutcomeCallable EC2Client::CreateSecurityGroupCallable(const CreateSecurityGroupRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateSecurityGroup, this, request);
}

void EC2Client::CreateSecurityGroupAsync(const CreateSecurityGroupRequest& request, const CreateSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateSecurityGroupAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateSecurityGroupAsyncHelper(const CreateSecurityGroupRequest& request, const CreateSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateSecurityGroup(request), context);
}

CreateSnapshotOutcome EC2Client::CreateSnapshot(const CreateSnapshotRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateSnapshotOutcome(CreateSnapshotResponse(outcome.GetResult()));
  }
  else
  {
    return CreateSnapshotOutcome(outcome.GetError());
  }
}

CreateSnapshotOutcomeCallable EC2Client::CreateSnapshotCallable(const CreateSnapshotRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateSnapshot, this, request);
}

void EC2Client::CreateSnapshotAsync(const CreateSnapshotRequest& request, const CreateSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateSnapshotAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateSnapshotAsyncHelper(const CreateSnapshotRequest& request, const CreateSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateSnapshot(request), context);
}

CreateSpotDatafeedSubscriptionOutcome EC2Client::CreateSpotDatafeedSubscription(const CreateSpotDatafeedSubscriptionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateSpotDatafeedSubscriptionOutcome(CreateSpotDatafeedSubscriptionResponse(outcome.GetResult()));
  }
  else
  {
    return CreateSpotDatafeedSubscriptionOutcome(outcome.GetError());
  }
}

CreateSpotDatafeedSubscriptionOutcomeCallable EC2Client::CreateSpotDatafeedSubscriptionCallable(const CreateSpotDatafeedSubscriptionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateSpotDatafeedSubscription, this, request);
}

void EC2Client::CreateSpotDatafeedSubscriptionAsync(const CreateSpotDatafeedSubscriptionRequest& request, const CreateSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateSpotDatafeedSubscriptionAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateSpotDatafeedSubscriptionAsyncHelper(const CreateSpotDatafeedSubscriptionRequest& request, const CreateSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateSpotDatafeedSubscription(request), context);
}

CreateSubnetOutcome EC2Client::CreateSubnet(const CreateSubnetRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateSubnetOutcome(CreateSubnetResponse(outcome.GetResult()));
  }
  else
  {
    return CreateSubnetOutcome(outcome.GetError());
  }
}

CreateSubnetOutcomeCallable EC2Client::CreateSubnetCallable(const CreateSubnetRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateSubnet, this, request);
}

void EC2Client::CreateSubnetAsync(const CreateSubnetRequest& request, const CreateSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateSubnetAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateSubnetAsyncHelper(const CreateSubnetRequest& request, const CreateSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateSubnet(request), context);
}

CreateTagsOutcome EC2Client::CreateTags(const CreateTagsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateTagsOutcome(NoResult());
  }
  else
  {
    return CreateTagsOutcome(outcome.GetError());
  }
}

CreateTagsOutcomeCallable EC2Client::CreateTagsCallable(const CreateTagsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateTags, this, request);
}

void EC2Client::CreateTagsAsync(const CreateTagsRequest& request, const CreateTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateTagsAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateTagsAsyncHelper(const CreateTagsRequest& request, const CreateTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateTags(request), context);
}

CreateVolumeOutcome EC2Client::CreateVolume(const CreateVolumeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVolumeOutcome(CreateVolumeResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVolumeOutcome(outcome.GetError());
  }
}

CreateVolumeOutcomeCallable EC2Client::CreateVolumeCallable(const CreateVolumeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVolume, this, request);
}

void EC2Client::CreateVolumeAsync(const CreateVolumeRequest& request, const CreateVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVolumeAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVolumeAsyncHelper(const CreateVolumeRequest& request, const CreateVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVolume(request), context);
}

CreateVpcOutcome EC2Client::CreateVpc(const CreateVpcRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpcOutcome(CreateVpcResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVpcOutcome(outcome.GetError());
  }
}

CreateVpcOutcomeCallable EC2Client::CreateVpcCallable(const CreateVpcRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpc, this, request);
}

void EC2Client::CreateVpcAsync(const CreateVpcRequest& request, const CreateVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpcAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpcAsyncHelper(const CreateVpcRequest& request, const CreateVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpc(request), context);
}

CreateVpcEndpointOutcome EC2Client::CreateVpcEndpoint(const CreateVpcEndpointRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpcEndpointOutcome(CreateVpcEndpointResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVpcEndpointOutcome(outcome.GetError());
  }
}

CreateVpcEndpointOutcomeCallable EC2Client::CreateVpcEndpointCallable(const CreateVpcEndpointRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpcEndpoint, this, request);
}

void EC2Client::CreateVpcEndpointAsync(const CreateVpcEndpointRequest& request, const CreateVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpcEndpointAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpcEndpointAsyncHelper(const CreateVpcEndpointRequest& request, const CreateVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpcEndpoint(request), context);
}

