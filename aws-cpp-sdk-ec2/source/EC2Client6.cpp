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

DescribeSpotInstanceRequestsOutcome EC2Client::DescribeSpotInstanceRequests(const DescribeSpotInstanceRequestsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotInstanceRequestsOutcome(DescribeSpotInstanceRequestsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotInstanceRequestsOutcome(outcome.GetError());
  }
}

DescribeSpotInstanceRequestsOutcomeCallable EC2Client::DescribeSpotInstanceRequestsCallable(const DescribeSpotInstanceRequestsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotInstanceRequests, this, request);
}

void EC2Client::DescribeSpotInstanceRequestsAsync(const DescribeSpotInstanceRequestsRequest& request, const DescribeSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotInstanceRequestsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotInstanceRequestsAsyncHelper(const DescribeSpotInstanceRequestsRequest& request, const DescribeSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotInstanceRequests(request), context);
}

DescribeSpotPriceHistoryOutcome EC2Client::DescribeSpotPriceHistory(const DescribeSpotPriceHistoryRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotPriceHistoryOutcome(DescribeSpotPriceHistoryResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotPriceHistoryOutcome(outcome.GetError());
  }
}

DescribeSpotPriceHistoryOutcomeCallable EC2Client::DescribeSpotPriceHistoryCallable(const DescribeSpotPriceHistoryRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotPriceHistory, this, request);
}

void EC2Client::DescribeSpotPriceHistoryAsync(const DescribeSpotPriceHistoryRequest& request, const DescribeSpotPriceHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotPriceHistoryAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotPriceHistoryAsyncHelper(const DescribeSpotPriceHistoryRequest& request, const DescribeSpotPriceHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotPriceHistory(request), context);
}

DescribeSubnetsOutcome EC2Client::DescribeSubnets(const DescribeSubnetsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSubnetsOutcome(DescribeSubnetsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSubnetsOutcome(outcome.GetError());
  }
}

DescribeSubnetsOutcomeCallable EC2Client::DescribeSubnetsCallable(const DescribeSubnetsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSubnets, this, request);
}

void EC2Client::DescribeSubnetsAsync(const DescribeSubnetsRequest& request, const DescribeSubnetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSubnetsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSubnetsAsyncHelper(const DescribeSubnetsRequest& request, const DescribeSubnetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSubnets(request), context);
}

DescribeTagsOutcome EC2Client::DescribeTags(const DescribeTagsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeTagsOutcome(DescribeTagsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeTagsOutcome(outcome.GetError());
  }
}

DescribeTagsOutcomeCallable EC2Client::DescribeTagsCallable(const DescribeTagsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeTags, this, request);
}

void EC2Client::DescribeTagsAsync(const DescribeTagsRequest& request, const DescribeTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeTagsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeTagsAsyncHelper(const DescribeTagsRequest& request, const DescribeTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeTags(request), context);
}

DescribeVolumeAttributeOutcome EC2Client::DescribeVolumeAttribute(const DescribeVolumeAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVolumeAttributeOutcome(DescribeVolumeAttributeResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVolumeAttributeOutcome(outcome.GetError());
  }
}

DescribeVolumeAttributeOutcomeCallable EC2Client::DescribeVolumeAttributeCallable(const DescribeVolumeAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVolumeAttribute, this, request);
}

void EC2Client::DescribeVolumeAttributeAsync(const DescribeVolumeAttributeRequest& request, const DescribeVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVolumeAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVolumeAttributeAsyncHelper(const DescribeVolumeAttributeRequest& request, const DescribeVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVolumeAttribute(request), context);
}

DescribeVolumeStatusOutcome EC2Client::DescribeVolumeStatus(const DescribeVolumeStatusRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVolumeStatusOutcome(DescribeVolumeStatusResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVolumeStatusOutcome(outcome.GetError());
  }
}

DescribeVolumeStatusOutcomeCallable EC2Client::DescribeVolumeStatusCallable(const DescribeVolumeStatusRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVolumeStatus, this, request);
}

void EC2Client::DescribeVolumeStatusAsync(const DescribeVolumeStatusRequest& request, const DescribeVolumeStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVolumeStatusAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVolumeStatusAsyncHelper(const DescribeVolumeStatusRequest& request, const DescribeVolumeStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVolumeStatus(request), context);
}

DescribeVolumesOutcome EC2Client::DescribeVolumes(const DescribeVolumesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVolumesOutcome(DescribeVolumesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVolumesOutcome(outcome.GetError());
  }
}

DescribeVolumesOutcomeCallable EC2Client::DescribeVolumesCallable(const DescribeVolumesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVolumes, this, request);
}

void EC2Client::DescribeVolumesAsync(const DescribeVolumesRequest& request, const DescribeVolumesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVolumesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVolumesAsyncHelper(const DescribeVolumesRequest& request, const DescribeVolumesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVolumes(request), context);
}

DescribeVpcAttributeOutcome EC2Client::DescribeVpcAttribute(const DescribeVpcAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcAttributeOutcome(DescribeVpcAttributeResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcAttributeOutcome(outcome.GetError());
  }
}

DescribeVpcAttributeOutcomeCallable EC2Client::DescribeVpcAttributeCallable(const DescribeVpcAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcAttribute, this, request);
}

void EC2Client::DescribeVpcAttributeAsync(const DescribeVpcAttributeRequest& request, const DescribeVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcAttributeAsyncHelper(const DescribeVpcAttributeRequest& request, const DescribeVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcAttribute(request), context);
}

DescribeVpcClassicLinkOutcome EC2Client::DescribeVpcClassicLink(const DescribeVpcClassicLinkRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcClassicLinkOutcome(DescribeVpcClassicLinkResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcClassicLinkOutcome(outcome.GetError());
  }
}

DescribeVpcClassicLinkOutcomeCallable EC2Client::DescribeVpcClassicLinkCallable(const DescribeVpcClassicLinkRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcClassicLink, this, request);
}

void EC2Client::DescribeVpcClassicLinkAsync(const DescribeVpcClassicLinkRequest& request, const DescribeVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcClassicLinkAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcClassicLinkAsyncHelper(const DescribeVpcClassicLinkRequest& request, const DescribeVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcClassicLink(request), context);
}

DescribeVpcClassicLinkDnsSupportOutcome EC2Client::DescribeVpcClassicLinkDnsSupport(const DescribeVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcClassicLinkDnsSupportOutcome(DescribeVpcClassicLinkDnsSupportResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcClassicLinkDnsSupportOutcome(outcome.GetError());
  }
}

DescribeVpcClassicLinkDnsSupportOutcomeCallable EC2Client::DescribeVpcClassicLinkDnsSupportCallable(const DescribeVpcClassicLinkDnsSupportRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcClassicLinkDnsSupport, this, request);
}

void EC2Client::DescribeVpcClassicLinkDnsSupportAsync(const DescribeVpcClassicLinkDnsSupportRequest& request, const DescribeVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcClassicLinkDnsSupportAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcClassicLinkDnsSupportAsyncHelper(const DescribeVpcClassicLinkDnsSupportRequest& request, const DescribeVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcClassicLinkDnsSupport(request), context);
}

DescribeVpcEndpointServicesOutcome EC2Client::DescribeVpcEndpointServices(const DescribeVpcEndpointServicesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcEndpointServicesOutcome(DescribeVpcEndpointServicesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcEndpointServicesOutcome(outcome.GetError());
  }
}

DescribeVpcEndpointServicesOutcomeCallable EC2Client::DescribeVpcEndpointServicesCallable(const DescribeVpcEndpointServicesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcEndpointServices, this, request);
}

void EC2Client::DescribeVpcEndpointServicesAsync(const DescribeVpcEndpointServicesRequest& request, const DescribeVpcEndpointServicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcEndpointServicesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcEndpointServicesAsyncHelper(const DescribeVpcEndpointServicesRequest& request, const DescribeVpcEndpointServicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcEndpointServices(request), context);
}

DescribeVpcEndpointsOutcome EC2Client::DescribeVpcEndpoints(const DescribeVpcEndpointsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcEndpointsOutcome(DescribeVpcEndpointsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcEndpointsOutcome(outcome.GetError());
  }
}

DescribeVpcEndpointsOutcomeCallable EC2Client::DescribeVpcEndpointsCallable(const DescribeVpcEndpointsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcEndpoints, this, request);
}

void EC2Client::DescribeVpcEndpointsAsync(const DescribeVpcEndpointsRequest& request, const DescribeVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcEndpointsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcEndpointsAsyncHelper(const DescribeVpcEndpointsRequest& request, const DescribeVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcEndpoints(request), context);
}

DescribeVpcPeeringConnectionsOutcome EC2Client::DescribeVpcPeeringConnections(const DescribeVpcPeeringConnectionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcPeeringConnectionsOutcome(DescribeVpcPeeringConnectionsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcPeeringConnectionsOutcome(outcome.GetError());
  }
}

DescribeVpcPeeringConnectionsOutcomeCallable EC2Client::DescribeVpcPeeringConnectionsCallable(const DescribeVpcPeeringConnectionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcPeeringConnections, this, request);
}

void EC2Client::DescribeVpcPeeringConnectionsAsync(const DescribeVpcPeeringConnectionsRequest& request, const DescribeVpcPeeringConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcPeeringConnectionsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcPeeringConnectionsAsyncHelper(const DescribeVpcPeeringConnectionsRequest& request, const DescribeVpcPeeringConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcPeeringConnections(request), context);
}

DescribeVpcsOutcome EC2Client::DescribeVpcs(const DescribeVpcsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpcsOutcome(DescribeVpcsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpcsOutcome(outcome.GetError());
  }
}

DescribeVpcsOutcomeCallable EC2Client::DescribeVpcsCallable(const DescribeVpcsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpcs, this, request);
}

void EC2Client::DescribeVpcsAsync(const DescribeVpcsRequest& request, const DescribeVpcsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpcsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpcsAsyncHelper(const DescribeVpcsRequest& request, const DescribeVpcsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpcs(request), context);
}

DescribeVpnConnectionsOutcome EC2Client::DescribeVpnConnections(const DescribeVpnConnectionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpnConnectionsOutcome(DescribeVpnConnectionsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpnConnectionsOutcome(outcome.GetError());
  }
}

DescribeVpnConnectionsOutcomeCallable EC2Client::DescribeVpnConnectionsCallable(const DescribeVpnConnectionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpnConnections, this, request);
}

void EC2Client::DescribeVpnConnectionsAsync(const DescribeVpnConnectionsRequest& request, const DescribeVpnConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpnConnectionsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpnConnectionsAsyncHelper(const DescribeVpnConnectionsRequest& request, const DescribeVpnConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpnConnections(request), context);
}

DescribeVpnGatewaysOutcome EC2Client::DescribeVpnGateways(const DescribeVpnGatewaysRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeVpnGatewaysOutcome(DescribeVpnGatewaysResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeVpnGatewaysOutcome(outcome.GetError());
  }
}

DescribeVpnGatewaysOutcomeCallable EC2Client::DescribeVpnGatewaysCallable(const DescribeVpnGatewaysRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeVpnGateways, this, request);
}

void EC2Client::DescribeVpnGatewaysAsync(const DescribeVpnGatewaysRequest& request, const DescribeVpnGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeVpnGatewaysAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeVpnGatewaysAsyncHelper(const DescribeVpnGatewaysRequest& request, const DescribeVpnGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeVpnGateways(request), context);
}

DetachClassicLinkVpcOutcome EC2Client::DetachClassicLinkVpc(const DetachClassicLinkVpcRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DetachClassicLinkVpcOutcome(DetachClassicLinkVpcResponse(outcome.GetResult()));
  }
  else
  {
    return DetachClassicLinkVpcOutcome(outcome.GetError());
  }
}

DetachClassicLinkVpcOutcomeCallable EC2Client::DetachClassicLinkVpcCallable(const DetachClassicLinkVpcRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DetachClassicLinkVpc, this, request);
}

void EC2Client::DetachClassicLinkVpcAsync(const DetachClassicLinkVpcRequest& request, const DetachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DetachClassicLinkVpcAsyncHelper, this, request, handler, context);
}

void EC2Client::DetachClassicLinkVpcAsyncHelper(const DetachClassicLinkVpcRequest& request, const DetachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DetachClassicLinkVpc(request), context);
}

DetachInternetGatewayOutcome EC2Client::DetachInternetGateway(const DetachInternetGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DetachInternetGatewayOutcome(NoResult());
  }
  else
  {
    return DetachInternetGatewayOutcome(outcome.GetError());
  }
}

DetachInternetGatewayOutcomeCallable EC2Client::DetachInternetGatewayCallable(const DetachInternetGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DetachInternetGateway, this, request);
}

void EC2Client::DetachInternetGatewayAsync(const DetachInternetGatewayRequest& request, const DetachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DetachInternetGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::DetachInternetGatewayAsyncHelper(const DetachInternetGatewayRequest& request, const DetachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DetachInternetGateway(request), context);
}

DetachNetworkInterfaceOutcome EC2Client::DetachNetworkInterface(const DetachNetworkInterfaceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DetachNetworkInterfaceOutcome(NoResult());
  }
  else
  {
    return DetachNetworkInterfaceOutcome(outcome.GetError());
  }
}

DetachNetworkInterfaceOutcomeCallable EC2Client::DetachNetworkInterfaceCallable(const DetachNetworkInterfaceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DetachNetworkInterface, this, request);
}

void EC2Client::DetachNetworkInterfaceAsync(const DetachNetworkInterfaceRequest& request, const DetachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DetachNetworkInterfaceAsyncHelper, this, request, handler, context);
}

void EC2Client::DetachNetworkInterfaceAsyncHelper(const DetachNetworkInterfaceRequest& request, const DetachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DetachNetworkInterface(request), context);
}

DetachVolumeOutcome EC2Client::DetachVolume(const DetachVolumeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DetachVolumeOutcome(DetachVolumeResponse(outcome.GetResult()));
  }
  else
  {
    return DetachVolumeOutcome(outcome.GetError());
  }
}

DetachVolumeOutcomeCallable EC2Client::DetachVolumeCallable(const DetachVolumeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DetachVolume, this, request);
}

void EC2Client::DetachVolumeAsync(const DetachVolumeRequest& request, const DetachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DetachVolumeAsyncHelper, this, request, handler, context);
}

void EC2Client::DetachVolumeAsyncHelper(const DetachVolumeRequest& request, const DetachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DetachVolume(request), context);
}

DetachVpnGatewayOutcome EC2Client::DetachVpnGateway(const DetachVpnGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DetachVpnGatewayOutcome(NoResult());
  }
  else
  {
    return DetachVpnGatewayOutcome(outcome.GetError());
  }
}

DetachVpnGatewayOutcomeCallable EC2Client::DetachVpnGatewayCallable(const DetachVpnGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DetachVpnGateway, this, request);
}

void EC2Client::DetachVpnGatewayAsync(const DetachVpnGatewayRequest& request, const DetachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DetachVpnGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::DetachVpnGatewayAsyncHelper(const DetachVpnGatewayRequest& request, const DetachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DetachVpnGateway(request), context);
}

DisableVgwRoutePropagationOutcome EC2Client::DisableVgwRoutePropagation(const DisableVgwRoutePropagationRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DisableVgwRoutePropagationOutcome(NoResult());
  }
  else
  {
    return DisableVgwRoutePropagationOutcome(outcome.GetError());
  }
}

DisableVgwRoutePropagationOutcomeCallable EC2Client::DisableVgwRoutePropagationCallable(const DisableVgwRoutePropagationRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DisableVgwRoutePropagation, this, request);
}

void EC2Client::DisableVgwRoutePropagationAsync(const DisableVgwRoutePropagationRequest& request, const DisableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DisableVgwRoutePropagationAsyncHelper, this, request, handler, context);
}

void EC2Client::DisableVgwRoutePropagationAsyncHelper(const DisableVgwRoutePropagationRequest& request, const DisableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DisableVgwRoutePropagation(request), context);
}

DisableVpcClassicLinkOutcome EC2Client::DisableVpcClassicLink(const DisableVpcClassicLinkRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DisableVpcClassicLinkOutcome(DisableVpcClassicLinkResponse(outcome.GetResult()));
  }
  else
  {
    return DisableVpcClassicLinkOutcome(outcome.GetError());
  }
}

DisableVpcClassicLinkOutcomeCallable EC2Client::DisableVpcClassicLinkCallable(const DisableVpcClassicLinkRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DisableVpcClassicLink, this, request);
}

void EC2Client::DisableVpcClassicLinkAsync(const DisableVpcClassicLinkRequest& request, const DisableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DisableVpcClassicLinkAsyncHelper, this, request, handler, context);
}

void EC2Client::DisableVpcClassicLinkAsyncHelper(const DisableVpcClassicLinkRequest& request, const DisableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DisableVpcClassicLink(request), context);
}

DisableVpcClassicLinkDnsSupportOutcome EC2Client::DisableVpcClassicLinkDnsSupport(const DisableVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DisableVpcClassicLinkDnsSupportOutcome(DisableVpcClassicLinkDnsSupportResponse(outcome.GetResult()));
  }
  else
  {
    return DisableVpcClassicLinkDnsSupportOutcome(outcome.GetError());
  }
}

DisableVpcClassicLinkDnsSupportOutcomeCallable EC2Client::DisableVpcClassicLinkDnsSupportCallable(const DisableVpcClassicLinkDnsSupportRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DisableVpcClassicLinkDnsSupport, this, request);
}

void EC2Client::DisableVpcClassicLinkDnsSupportAsync(const DisableVpcClassicLinkDnsSupportRequest& request, const DisableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DisableVpcClassicLinkDnsSupportAsyncHelper, this, request, handler, context);
}

void EC2Client::DisableVpcClassicLinkDnsSupportAsyncHelper(const DisableVpcClassicLinkDnsSupportRequest& request, const DisableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DisableVpcClassicLinkDnsSupport(request), context);
}

DisassociateAddressOutcome EC2Client::DisassociateAddress(const DisassociateAddressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DisassociateAddressOutcome(NoResult());
  }
  else
  {
    return DisassociateAddressOutcome(outcome.GetError());
  }
}

DisassociateAddressOutcomeCallable EC2Client::DisassociateAddressCallable(const DisassociateAddressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DisassociateAddress, this, request);
}

void EC2Client::DisassociateAddressAsync(const DisassociateAddressRequest& request, const DisassociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DisassociateAddressAsyncHelper, this, request, handler, context);
}

void EC2Client::DisassociateAddressAsyncHelper(const DisassociateAddressRequest& request, const DisassociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DisassociateAddress(request), context);
}

