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

DescribeInternetGatewaysOutcome EC2Client::DescribeInternetGateways(const DescribeInternetGatewaysRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeInternetGatewaysOutcome(DescribeInternetGatewaysResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeInternetGatewaysOutcome(outcome.GetError());
  }
}

DescribeInternetGatewaysOutcomeCallable EC2Client::DescribeInternetGatewaysCallable(const DescribeInternetGatewaysRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeInternetGateways, this, request);
}

void EC2Client::DescribeInternetGatewaysAsync(const DescribeInternetGatewaysRequest& request, const DescribeInternetGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeInternetGatewaysAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeInternetGatewaysAsyncHelper(const DescribeInternetGatewaysRequest& request, const DescribeInternetGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeInternetGateways(request), context);
}

DescribeKeyPairsOutcome EC2Client::DescribeKeyPairs(const DescribeKeyPairsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeKeyPairsOutcome(DescribeKeyPairsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeKeyPairsOutcome(outcome.GetError());
  }
}

DescribeKeyPairsOutcomeCallable EC2Client::DescribeKeyPairsCallable(const DescribeKeyPairsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeKeyPairs, this, request);
}

void EC2Client::DescribeKeyPairsAsync(const DescribeKeyPairsRequest& request, const DescribeKeyPairsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeKeyPairsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeKeyPairsAsyncHelper(const DescribeKeyPairsRequest& request, const DescribeKeyPairsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeKeyPairs(request), context);
}

DescribeMovingAddressesOutcome EC2Client::DescribeMovingAddresses(const DescribeMovingAddressesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeMovingAddressesOutcome(DescribeMovingAddressesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeMovingAddressesOutcome(outcome.GetError());
  }
}

DescribeMovingAddressesOutcomeCallable EC2Client::DescribeMovingAddressesCallable(const DescribeMovingAddressesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeMovingAddresses, this, request);
}

void EC2Client::DescribeMovingAddressesAsync(const DescribeMovingAddressesRequest& request, const DescribeMovingAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeMovingAddressesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeMovingAddressesAsyncHelper(const DescribeMovingAddressesRequest& request, const DescribeMovingAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeMovingAddresses(request), context);
}

DescribeNatGatewaysOutcome EC2Client::DescribeNatGateways(const DescribeNatGatewaysRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeNatGatewaysOutcome(DescribeNatGatewaysResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeNatGatewaysOutcome(outcome.GetError());
  }
}

DescribeNatGatewaysOutcomeCallable EC2Client::DescribeNatGatewaysCallable(const DescribeNatGatewaysRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeNatGateways, this, request);
}

void EC2Client::DescribeNatGatewaysAsync(const DescribeNatGatewaysRequest& request, const DescribeNatGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeNatGatewaysAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeNatGatewaysAsyncHelper(const DescribeNatGatewaysRequest& request, const DescribeNatGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeNatGateways(request), context);
}

DescribeNetworkAclsOutcome EC2Client::DescribeNetworkAcls(const DescribeNetworkAclsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeNetworkAclsOutcome(DescribeNetworkAclsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeNetworkAclsOutcome(outcome.GetError());
  }
}

DescribeNetworkAclsOutcomeCallable EC2Client::DescribeNetworkAclsCallable(const DescribeNetworkAclsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeNetworkAcls, this, request);
}

void EC2Client::DescribeNetworkAclsAsync(const DescribeNetworkAclsRequest& request, const DescribeNetworkAclsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeNetworkAclsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeNetworkAclsAsyncHelper(const DescribeNetworkAclsRequest& request, const DescribeNetworkAclsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeNetworkAcls(request), context);
}

DescribeNetworkInterfaceAttributeOutcome EC2Client::DescribeNetworkInterfaceAttribute(const DescribeNetworkInterfaceAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeNetworkInterfaceAttributeOutcome(DescribeNetworkInterfaceAttributeResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeNetworkInterfaceAttributeOutcome(outcome.GetError());
  }
}

DescribeNetworkInterfaceAttributeOutcomeCallable EC2Client::DescribeNetworkInterfaceAttributeCallable(const DescribeNetworkInterfaceAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeNetworkInterfaceAttribute, this, request);
}

void EC2Client::DescribeNetworkInterfaceAttributeAsync(const DescribeNetworkInterfaceAttributeRequest& request, const DescribeNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeNetworkInterfaceAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeNetworkInterfaceAttributeAsyncHelper(const DescribeNetworkInterfaceAttributeRequest& request, const DescribeNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeNetworkInterfaceAttribute(request), context);
}

DescribeNetworkInterfacesOutcome EC2Client::DescribeNetworkInterfaces(const DescribeNetworkInterfacesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeNetworkInterfacesOutcome(DescribeNetworkInterfacesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeNetworkInterfacesOutcome(outcome.GetError());
  }
}

DescribeNetworkInterfacesOutcomeCallable EC2Client::DescribeNetworkInterfacesCallable(const DescribeNetworkInterfacesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeNetworkInterfaces, this, request);
}

void EC2Client::DescribeNetworkInterfacesAsync(const DescribeNetworkInterfacesRequest& request, const DescribeNetworkInterfacesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeNetworkInterfacesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeNetworkInterfacesAsyncHelper(const DescribeNetworkInterfacesRequest& request, const DescribeNetworkInterfacesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeNetworkInterfaces(request), context);
}

DescribePlacementGroupsOutcome EC2Client::DescribePlacementGroups(const DescribePlacementGroupsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribePlacementGroupsOutcome(DescribePlacementGroupsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribePlacementGroupsOutcome(outcome.GetError());
  }
}

DescribePlacementGroupsOutcomeCallable EC2Client::DescribePlacementGroupsCallable(const DescribePlacementGroupsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribePlacementGroups, this, request);
}

void EC2Client::DescribePlacementGroupsAsync(const DescribePlacementGroupsRequest& request, const DescribePlacementGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribePlacementGroupsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribePlacementGroupsAsyncHelper(const DescribePlacementGroupsRequest& request, const DescribePlacementGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribePlacementGroups(request), context);
}

DescribePrefixListsOutcome EC2Client::DescribePrefixLists(const DescribePrefixListsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribePrefixListsOutcome(DescribePrefixListsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribePrefixListsOutcome(outcome.GetError());
  }
}

DescribePrefixListsOutcomeCallable EC2Client::DescribePrefixListsCallable(const DescribePrefixListsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribePrefixLists, this, request);
}

void EC2Client::DescribePrefixListsAsync(const DescribePrefixListsRequest& request, const DescribePrefixListsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribePrefixListsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribePrefixListsAsyncHelper(const DescribePrefixListsRequest& request, const DescribePrefixListsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribePrefixLists(request), context);
}

DescribeRegionsOutcome EC2Client::DescribeRegions(const DescribeRegionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeRegionsOutcome(DescribeRegionsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeRegionsOutcome(outcome.GetError());
  }
}

DescribeRegionsOutcomeCallable EC2Client::DescribeRegionsCallable(const DescribeRegionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeRegions, this, request);
}

void EC2Client::DescribeRegionsAsync(const DescribeRegionsRequest& request, const DescribeRegionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeRegionsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeRegionsAsyncHelper(const DescribeRegionsRequest& request, const DescribeRegionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeRegions(request), context);
}

DescribeReservedInstancesOutcome EC2Client::DescribeReservedInstances(const DescribeReservedInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeReservedInstancesOutcome(DescribeReservedInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeReservedInstancesOutcome(outcome.GetError());
  }
}

DescribeReservedInstancesOutcomeCallable EC2Client::DescribeReservedInstancesCallable(const DescribeReservedInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeReservedInstances, this, request);
}

void EC2Client::DescribeReservedInstancesAsync(const DescribeReservedInstancesRequest& request, const DescribeReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeReservedInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeReservedInstancesAsyncHelper(const DescribeReservedInstancesRequest& request, const DescribeReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeReservedInstances(request), context);
}

DescribeReservedInstancesListingsOutcome EC2Client::DescribeReservedInstancesListings(const DescribeReservedInstancesListingsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeReservedInstancesListingsOutcome(DescribeReservedInstancesListingsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeReservedInstancesListingsOutcome(outcome.GetError());
  }
}

DescribeReservedInstancesListingsOutcomeCallable EC2Client::DescribeReservedInstancesListingsCallable(const DescribeReservedInstancesListingsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeReservedInstancesListings, this, request);
}

void EC2Client::DescribeReservedInstancesListingsAsync(const DescribeReservedInstancesListingsRequest& request, const DescribeReservedInstancesListingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeReservedInstancesListingsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeReservedInstancesListingsAsyncHelper(const DescribeReservedInstancesListingsRequest& request, const DescribeReservedInstancesListingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeReservedInstancesListings(request), context);
}

DescribeReservedInstancesModificationsOutcome EC2Client::DescribeReservedInstancesModifications(const DescribeReservedInstancesModificationsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeReservedInstancesModificationsOutcome(DescribeReservedInstancesModificationsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeReservedInstancesModificationsOutcome(outcome.GetError());
  }
}

DescribeReservedInstancesModificationsOutcomeCallable EC2Client::DescribeReservedInstancesModificationsCallable(const DescribeReservedInstancesModificationsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeReservedInstancesModifications, this, request);
}

void EC2Client::DescribeReservedInstancesModificationsAsync(const DescribeReservedInstancesModificationsRequest& request, const DescribeReservedInstancesModificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeReservedInstancesModificationsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeReservedInstancesModificationsAsyncHelper(const DescribeReservedInstancesModificationsRequest& request, const DescribeReservedInstancesModificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeReservedInstancesModifications(request), context);
}

DescribeReservedInstancesOfferingsOutcome EC2Client::DescribeReservedInstancesOfferings(const DescribeReservedInstancesOfferingsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeReservedInstancesOfferingsOutcome(DescribeReservedInstancesOfferingsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeReservedInstancesOfferingsOutcome(outcome.GetError());
  }
}

DescribeReservedInstancesOfferingsOutcomeCallable EC2Client::DescribeReservedInstancesOfferingsCallable(const DescribeReservedInstancesOfferingsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeReservedInstancesOfferings, this, request);
}

void EC2Client::DescribeReservedInstancesOfferingsAsync(const DescribeReservedInstancesOfferingsRequest& request, const DescribeReservedInstancesOfferingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeReservedInstancesOfferingsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeReservedInstancesOfferingsAsyncHelper(const DescribeReservedInstancesOfferingsRequest& request, const DescribeReservedInstancesOfferingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeReservedInstancesOfferings(request), context);
}

DescribeRouteTablesOutcome EC2Client::DescribeRouteTables(const DescribeRouteTablesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeRouteTablesOutcome(DescribeRouteTablesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeRouteTablesOutcome(outcome.GetError());
  }
}

DescribeRouteTablesOutcomeCallable EC2Client::DescribeRouteTablesCallable(const DescribeRouteTablesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeRouteTables, this, request);
}

void EC2Client::DescribeRouteTablesAsync(const DescribeRouteTablesRequest& request, const DescribeRouteTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeRouteTablesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeRouteTablesAsyncHelper(const DescribeRouteTablesRequest& request, const DescribeRouteTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeRouteTables(request), context);
}

DescribeScheduledInstanceAvailabilityOutcome EC2Client::DescribeScheduledInstanceAvailability(const DescribeScheduledInstanceAvailabilityRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeScheduledInstanceAvailabilityOutcome(DescribeScheduledInstanceAvailabilityResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeScheduledInstanceAvailabilityOutcome(outcome.GetError());
  }
}

DescribeScheduledInstanceAvailabilityOutcomeCallable EC2Client::DescribeScheduledInstanceAvailabilityCallable(const DescribeScheduledInstanceAvailabilityRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeScheduledInstanceAvailability, this, request);
}

void EC2Client::DescribeScheduledInstanceAvailabilityAsync(const DescribeScheduledInstanceAvailabilityRequest& request, const DescribeScheduledInstanceAvailabilityResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeScheduledInstanceAvailabilityAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeScheduledInstanceAvailabilityAsyncHelper(const DescribeScheduledInstanceAvailabilityRequest& request, const DescribeScheduledInstanceAvailabilityResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeScheduledInstanceAvailability(request), context);
}

DescribeScheduledInstancesOutcome EC2Client::DescribeScheduledInstances(const DescribeScheduledInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeScheduledInstancesOutcome(DescribeScheduledInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeScheduledInstancesOutcome(outcome.GetError());
  }
}

DescribeScheduledInstancesOutcomeCallable EC2Client::DescribeScheduledInstancesCallable(const DescribeScheduledInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeScheduledInstances, this, request);
}

void EC2Client::DescribeScheduledInstancesAsync(const DescribeScheduledInstancesRequest& request, const DescribeScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeScheduledInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeScheduledInstancesAsyncHelper(const DescribeScheduledInstancesRequest& request, const DescribeScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeScheduledInstances(request), context);
}

DescribeSecurityGroupsOutcome EC2Client::DescribeSecurityGroups(const DescribeSecurityGroupsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSecurityGroupsOutcome(DescribeSecurityGroupsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSecurityGroupsOutcome(outcome.GetError());
  }
}

DescribeSecurityGroupsOutcomeCallable EC2Client::DescribeSecurityGroupsCallable(const DescribeSecurityGroupsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSecurityGroups, this, request);
}

void EC2Client::DescribeSecurityGroupsAsync(const DescribeSecurityGroupsRequest& request, const DescribeSecurityGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSecurityGroupsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSecurityGroupsAsyncHelper(const DescribeSecurityGroupsRequest& request, const DescribeSecurityGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSecurityGroups(request), context);
}

DescribeSnapshotAttributeOutcome EC2Client::DescribeSnapshotAttribute(const DescribeSnapshotAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSnapshotAttributeOutcome(DescribeSnapshotAttributeResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSnapshotAttributeOutcome(outcome.GetError());
  }
}

DescribeSnapshotAttributeOutcomeCallable EC2Client::DescribeSnapshotAttributeCallable(const DescribeSnapshotAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSnapshotAttribute, this, request);
}

void EC2Client::DescribeSnapshotAttributeAsync(const DescribeSnapshotAttributeRequest& request, const DescribeSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSnapshotAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSnapshotAttributeAsyncHelper(const DescribeSnapshotAttributeRequest& request, const DescribeSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSnapshotAttribute(request), context);
}

DescribeSnapshotsOutcome EC2Client::DescribeSnapshots(const DescribeSnapshotsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSnapshotsOutcome(DescribeSnapshotsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSnapshotsOutcome(outcome.GetError());
  }
}

DescribeSnapshotsOutcomeCallable EC2Client::DescribeSnapshotsCallable(const DescribeSnapshotsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSnapshots, this, request);
}

void EC2Client::DescribeSnapshotsAsync(const DescribeSnapshotsRequest& request, const DescribeSnapshotsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSnapshotsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSnapshotsAsyncHelper(const DescribeSnapshotsRequest& request, const DescribeSnapshotsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSnapshots(request), context);
}

DescribeSpotDatafeedSubscriptionOutcome EC2Client::DescribeSpotDatafeedSubscription(const DescribeSpotDatafeedSubscriptionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotDatafeedSubscriptionOutcome(DescribeSpotDatafeedSubscriptionResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotDatafeedSubscriptionOutcome(outcome.GetError());
  }
}

DescribeSpotDatafeedSubscriptionOutcomeCallable EC2Client::DescribeSpotDatafeedSubscriptionCallable(const DescribeSpotDatafeedSubscriptionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotDatafeedSubscription, this, request);
}

void EC2Client::DescribeSpotDatafeedSubscriptionAsync(const DescribeSpotDatafeedSubscriptionRequest& request, const DescribeSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotDatafeedSubscriptionAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotDatafeedSubscriptionAsyncHelper(const DescribeSpotDatafeedSubscriptionRequest& request, const DescribeSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotDatafeedSubscription(request), context);
}

DescribeSpotFleetInstancesOutcome EC2Client::DescribeSpotFleetInstances(const DescribeSpotFleetInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotFleetInstancesOutcome(DescribeSpotFleetInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotFleetInstancesOutcome(outcome.GetError());
  }
}

DescribeSpotFleetInstancesOutcomeCallable EC2Client::DescribeSpotFleetInstancesCallable(const DescribeSpotFleetInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotFleetInstances, this, request);
}

void EC2Client::DescribeSpotFleetInstancesAsync(const DescribeSpotFleetInstancesRequest& request, const DescribeSpotFleetInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotFleetInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotFleetInstancesAsyncHelper(const DescribeSpotFleetInstancesRequest& request, const DescribeSpotFleetInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotFleetInstances(request), context);
}

DescribeSpotFleetRequestHistoryOutcome EC2Client::DescribeSpotFleetRequestHistory(const DescribeSpotFleetRequestHistoryRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotFleetRequestHistoryOutcome(DescribeSpotFleetRequestHistoryResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotFleetRequestHistoryOutcome(outcome.GetError());
  }
}

DescribeSpotFleetRequestHistoryOutcomeCallable EC2Client::DescribeSpotFleetRequestHistoryCallable(const DescribeSpotFleetRequestHistoryRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotFleetRequestHistory, this, request);
}

void EC2Client::DescribeSpotFleetRequestHistoryAsync(const DescribeSpotFleetRequestHistoryRequest& request, const DescribeSpotFleetRequestHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotFleetRequestHistoryAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotFleetRequestHistoryAsyncHelper(const DescribeSpotFleetRequestHistoryRequest& request, const DescribeSpotFleetRequestHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotFleetRequestHistory(request), context);
}

DescribeSpotFleetRequestsOutcome EC2Client::DescribeSpotFleetRequests(const DescribeSpotFleetRequestsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeSpotFleetRequestsOutcome(DescribeSpotFleetRequestsResponse(outcome.GetResult()));
  }
  else
  {
    return DescribeSpotFleetRequestsOutcome(outcome.GetError());
  }
}

DescribeSpotFleetRequestsOutcomeCallable EC2Client::DescribeSpotFleetRequestsCallable(const DescribeSpotFleetRequestsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DescribeSpotFleetRequests, this, request);
}

void EC2Client::DescribeSpotFleetRequestsAsync(const DescribeSpotFleetRequestsRequest& request, const DescribeSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DescribeSpotFleetRequestsAsyncHelper, this, request, handler, context);
}

void EC2Client::DescribeSpotFleetRequestsAsyncHelper(const DescribeSpotFleetRequestsRequest& request, const DescribeSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeSpotFleetRequests(request), context);
}

