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


PurchaseReservedInstancesOfferingOutcome EC2Client::PurchaseReservedInstancesOffering(const PurchaseReservedInstancesOfferingRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return PurchaseReservedInstancesOfferingOutcome(PurchaseReservedInstancesOfferingResponse(outcome.GetResult()));
  }
  else
  {
    return PurchaseReservedInstancesOfferingOutcome(outcome.GetError());
  }
}

PurchaseReservedInstancesOfferingOutcomeCallable EC2Client::PurchaseReservedInstancesOfferingCallable(const PurchaseReservedInstancesOfferingRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::PurchaseReservedInstancesOffering, this, request);
}

void EC2Client::PurchaseReservedInstancesOfferingAsync(const PurchaseReservedInstancesOfferingRequest& request, const PurchaseReservedInstancesOfferingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::PurchaseReservedInstancesOfferingAsyncHelper, this, request, handler, context);
}

void EC2Client::PurchaseReservedInstancesOfferingAsyncHelper(const PurchaseReservedInstancesOfferingRequest& request, const PurchaseReservedInstancesOfferingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, PurchaseReservedInstancesOffering(request), context);
}

PurchaseScheduledInstancesOutcome EC2Client::PurchaseScheduledInstances(const PurchaseScheduledInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return PurchaseScheduledInstancesOutcome(PurchaseScheduledInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return PurchaseScheduledInstancesOutcome(outcome.GetError());
  }
}

PurchaseScheduledInstancesOutcomeCallable EC2Client::PurchaseScheduledInstancesCallable(const PurchaseScheduledInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::PurchaseScheduledInstances, this, request);
}

void EC2Client::PurchaseScheduledInstancesAsync(const PurchaseScheduledInstancesRequest& request, const PurchaseScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::PurchaseScheduledInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::PurchaseScheduledInstancesAsyncHelper(const PurchaseScheduledInstancesRequest& request, const PurchaseScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, PurchaseScheduledInstances(request), context);
}

RebootInstancesOutcome EC2Client::RebootInstances(const RebootInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RebootInstancesOutcome(NoResult());
  }
  else
  {
    return RebootInstancesOutcome(outcome.GetError());
  }
}

RebootInstancesOutcomeCallable EC2Client::RebootInstancesCallable(const RebootInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RebootInstances, this, request);
}

void EC2Client::RebootInstancesAsync(const RebootInstancesRequest& request, const RebootInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RebootInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::RebootInstancesAsyncHelper(const RebootInstancesRequest& request, const RebootInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RebootInstances(request), context);
}

RegisterImageOutcome EC2Client::RegisterImage(const RegisterImageRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RegisterImageOutcome(RegisterImageResponse(outcome.GetResult()));
  }
  else
  {
    return RegisterImageOutcome(outcome.GetError());
  }
}

RegisterImageOutcomeCallable EC2Client::RegisterImageCallable(const RegisterImageRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RegisterImage, this, request);
}

void EC2Client::RegisterImageAsync(const RegisterImageRequest& request, const RegisterImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RegisterImageAsyncHelper, this, request, handler, context);
}

void EC2Client::RegisterImageAsyncHelper(const RegisterImageRequest& request, const RegisterImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RegisterImage(request), context);
}

RejectVpcPeeringConnectionOutcome EC2Client::RejectVpcPeeringConnection(const RejectVpcPeeringConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RejectVpcPeeringConnectionOutcome(RejectVpcPeeringConnectionResponse(outcome.GetResult()));
  }
  else
  {
    return RejectVpcPeeringConnectionOutcome(outcome.GetError());
  }
}

RejectVpcPeeringConnectionOutcomeCallable EC2Client::RejectVpcPeeringConnectionCallable(const RejectVpcPeeringConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RejectVpcPeeringConnection, this, request);
}

void EC2Client::RejectVpcPeeringConnectionAsync(const RejectVpcPeeringConnectionRequest& request, const RejectVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RejectVpcPeeringConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::RejectVpcPeeringConnectionAsyncHelper(const RejectVpcPeeringConnectionRequest& request, const RejectVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RejectVpcPeeringConnection(request), context);
}

ReleaseAddressOutcome EC2Client::ReleaseAddress(const ReleaseAddressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReleaseAddressOutcome(NoResult());
  }
  else
  {
    return ReleaseAddressOutcome(outcome.GetError());
  }
}

ReleaseAddressOutcomeCallable EC2Client::ReleaseAddressCallable(const ReleaseAddressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReleaseAddress, this, request);
}

void EC2Client::ReleaseAddressAsync(const ReleaseAddressRequest& request, const ReleaseAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReleaseAddressAsyncHelper, this, request, handler, context);
}

void EC2Client::ReleaseAddressAsyncHelper(const ReleaseAddressRequest& request, const ReleaseAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReleaseAddress(request), context);
}

ReleaseHostsOutcome EC2Client::ReleaseHosts(const ReleaseHostsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReleaseHostsOutcome(ReleaseHostsResponse(outcome.GetResult()));
  }
  else
  {
    return ReleaseHostsOutcome(outcome.GetError());
  }
}

ReleaseHostsOutcomeCallable EC2Client::ReleaseHostsCallable(const ReleaseHostsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReleaseHosts, this, request);
}

void EC2Client::ReleaseHostsAsync(const ReleaseHostsRequest& request, const ReleaseHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReleaseHostsAsyncHelper, this, request, handler, context);
}

void EC2Client::ReleaseHostsAsyncHelper(const ReleaseHostsRequest& request, const ReleaseHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReleaseHosts(request), context);
}

ReplaceNetworkAclAssociationOutcome EC2Client::ReplaceNetworkAclAssociation(const ReplaceNetworkAclAssociationRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReplaceNetworkAclAssociationOutcome(ReplaceNetworkAclAssociationResponse(outcome.GetResult()));
  }
  else
  {
    return ReplaceNetworkAclAssociationOutcome(outcome.GetError());
  }
}

ReplaceNetworkAclAssociationOutcomeCallable EC2Client::ReplaceNetworkAclAssociationCallable(const ReplaceNetworkAclAssociationRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReplaceNetworkAclAssociation, this, request);
}

void EC2Client::ReplaceNetworkAclAssociationAsync(const ReplaceNetworkAclAssociationRequest& request, const ReplaceNetworkAclAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReplaceNetworkAclAssociationAsyncHelper, this, request, handler, context);
}

void EC2Client::ReplaceNetworkAclAssociationAsyncHelper(const ReplaceNetworkAclAssociationRequest& request, const ReplaceNetworkAclAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReplaceNetworkAclAssociation(request), context);
}

ReplaceNetworkAclEntryOutcome EC2Client::ReplaceNetworkAclEntry(const ReplaceNetworkAclEntryRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReplaceNetworkAclEntryOutcome(NoResult());
  }
  else
  {
    return ReplaceNetworkAclEntryOutcome(outcome.GetError());
  }
}

ReplaceNetworkAclEntryOutcomeCallable EC2Client::ReplaceNetworkAclEntryCallable(const ReplaceNetworkAclEntryRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReplaceNetworkAclEntry, this, request);
}

void EC2Client::ReplaceNetworkAclEntryAsync(const ReplaceNetworkAclEntryRequest& request, const ReplaceNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReplaceNetworkAclEntryAsyncHelper, this, request, handler, context);
}

void EC2Client::ReplaceNetworkAclEntryAsyncHelper(const ReplaceNetworkAclEntryRequest& request, const ReplaceNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReplaceNetworkAclEntry(request), context);
}

ReplaceRouteOutcome EC2Client::ReplaceRoute(const ReplaceRouteRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReplaceRouteOutcome(NoResult());
  }
  else
  {
    return ReplaceRouteOutcome(outcome.GetError());
  }
}

ReplaceRouteOutcomeCallable EC2Client::ReplaceRouteCallable(const ReplaceRouteRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReplaceRoute, this, request);
}

void EC2Client::ReplaceRouteAsync(const ReplaceRouteRequest& request, const ReplaceRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReplaceRouteAsyncHelper, this, request, handler, context);
}

void EC2Client::ReplaceRouteAsyncHelper(const ReplaceRouteRequest& request, const ReplaceRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReplaceRoute(request), context);
}

ReplaceRouteTableAssociationOutcome EC2Client::ReplaceRouteTableAssociation(const ReplaceRouteTableAssociationRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReplaceRouteTableAssociationOutcome(ReplaceRouteTableAssociationResponse(outcome.GetResult()));
  }
  else
  {
    return ReplaceRouteTableAssociationOutcome(outcome.GetError());
  }
}

ReplaceRouteTableAssociationOutcomeCallable EC2Client::ReplaceRouteTableAssociationCallable(const ReplaceRouteTableAssociationRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReplaceRouteTableAssociation, this, request);
}

void EC2Client::ReplaceRouteTableAssociationAsync(const ReplaceRouteTableAssociationRequest& request, const ReplaceRouteTableAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReplaceRouteTableAssociationAsyncHelper, this, request, handler, context);
}

void EC2Client::ReplaceRouteTableAssociationAsyncHelper(const ReplaceRouteTableAssociationRequest& request, const ReplaceRouteTableAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReplaceRouteTableAssociation(request), context);
}

ReportInstanceStatusOutcome EC2Client::ReportInstanceStatus(const ReportInstanceStatusRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ReportInstanceStatusOutcome(NoResult());
  }
  else
  {
    return ReportInstanceStatusOutcome(outcome.GetError());
  }
}

ReportInstanceStatusOutcomeCallable EC2Client::ReportInstanceStatusCallable(const ReportInstanceStatusRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ReportInstanceStatus, this, request);
}

void EC2Client::ReportInstanceStatusAsync(const ReportInstanceStatusRequest& request, const ReportInstanceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ReportInstanceStatusAsyncHelper, this, request, handler, context);
}

void EC2Client::ReportInstanceStatusAsyncHelper(const ReportInstanceStatusRequest& request, const ReportInstanceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ReportInstanceStatus(request), context);
}

RequestSpotFleetOutcome EC2Client::RequestSpotFleet(const RequestSpotFleetRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RequestSpotFleetOutcome(RequestSpotFleetResponse(outcome.GetResult()));
  }
  else
  {
    return RequestSpotFleetOutcome(outcome.GetError());
  }
}

RequestSpotFleetOutcomeCallable EC2Client::RequestSpotFleetCallable(const RequestSpotFleetRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RequestSpotFleet, this, request);
}

void EC2Client::RequestSpotFleetAsync(const RequestSpotFleetRequest& request, const RequestSpotFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RequestSpotFleetAsyncHelper, this, request, handler, context);
}

void EC2Client::RequestSpotFleetAsyncHelper(const RequestSpotFleetRequest& request, const RequestSpotFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RequestSpotFleet(request), context);
}

RequestSpotInstancesOutcome EC2Client::RequestSpotInstances(const RequestSpotInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RequestSpotInstancesOutcome(RequestSpotInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return RequestSpotInstancesOutcome(outcome.GetError());
  }
}

RequestSpotInstancesOutcomeCallable EC2Client::RequestSpotInstancesCallable(const RequestSpotInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RequestSpotInstances, this, request);
}

void EC2Client::RequestSpotInstancesAsync(const RequestSpotInstancesRequest& request, const RequestSpotInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RequestSpotInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::RequestSpotInstancesAsyncHelper(const RequestSpotInstancesRequest& request, const RequestSpotInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RequestSpotInstances(request), context);
}

ResetImageAttributeOutcome EC2Client::ResetImageAttribute(const ResetImageAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ResetImageAttributeOutcome(NoResult());
  }
  else
  {
    return ResetImageAttributeOutcome(outcome.GetError());
  }
}

ResetImageAttributeOutcomeCallable EC2Client::ResetImageAttributeCallable(const ResetImageAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ResetImageAttribute, this, request);
}

void EC2Client::ResetImageAttributeAsync(const ResetImageAttributeRequest& request, const ResetImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ResetImageAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ResetImageAttributeAsyncHelper(const ResetImageAttributeRequest& request, const ResetImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ResetImageAttribute(request), context);
}

ResetInstanceAttributeOutcome EC2Client::ResetInstanceAttribute(const ResetInstanceAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ResetInstanceAttributeOutcome(NoResult());
  }
  else
  {
    return ResetInstanceAttributeOutcome(outcome.GetError());
  }
}

ResetInstanceAttributeOutcomeCallable EC2Client::ResetInstanceAttributeCallable(const ResetInstanceAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ResetInstanceAttribute, this, request);
}

void EC2Client::ResetInstanceAttributeAsync(const ResetInstanceAttributeRequest& request, const ResetInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ResetInstanceAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ResetInstanceAttributeAsyncHelper(const ResetInstanceAttributeRequest& request, const ResetInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ResetInstanceAttribute(request), context);
}

ResetNetworkInterfaceAttributeOutcome EC2Client::ResetNetworkInterfaceAttribute(const ResetNetworkInterfaceAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ResetNetworkInterfaceAttributeOutcome(NoResult());
  }
  else
  {
    return ResetNetworkInterfaceAttributeOutcome(outcome.GetError());
  }
}

ResetNetworkInterfaceAttributeOutcomeCallable EC2Client::ResetNetworkInterfaceAttributeCallable(const ResetNetworkInterfaceAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ResetNetworkInterfaceAttribute, this, request);
}

void EC2Client::ResetNetworkInterfaceAttributeAsync(const ResetNetworkInterfaceAttributeRequest& request, const ResetNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ResetNetworkInterfaceAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ResetNetworkInterfaceAttributeAsyncHelper(const ResetNetworkInterfaceAttributeRequest& request, const ResetNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ResetNetworkInterfaceAttribute(request), context);
}

ResetSnapshotAttributeOutcome EC2Client::ResetSnapshotAttribute(const ResetSnapshotAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ResetSnapshotAttributeOutcome(NoResult());
  }
  else
  {
    return ResetSnapshotAttributeOutcome(outcome.GetError());
  }
}

ResetSnapshotAttributeOutcomeCallable EC2Client::ResetSnapshotAttributeCallable(const ResetSnapshotAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ResetSnapshotAttribute, this, request);
}

void EC2Client::ResetSnapshotAttributeAsync(const ResetSnapshotAttributeRequest& request, const ResetSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ResetSnapshotAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ResetSnapshotAttributeAsyncHelper(const ResetSnapshotAttributeRequest& request, const ResetSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ResetSnapshotAttribute(request), context);
}

RestoreAddressToClassicOutcome EC2Client::RestoreAddressToClassic(const RestoreAddressToClassicRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RestoreAddressToClassicOutcome(RestoreAddressToClassicResponse(outcome.GetResult()));
  }
  else
  {
    return RestoreAddressToClassicOutcome(outcome.GetError());
  }
}

RestoreAddressToClassicOutcomeCallable EC2Client::RestoreAddressToClassicCallable(const RestoreAddressToClassicRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RestoreAddressToClassic, this, request);
}

void EC2Client::RestoreAddressToClassicAsync(const RestoreAddressToClassicRequest& request, const RestoreAddressToClassicResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RestoreAddressToClassicAsyncHelper, this, request, handler, context);
}

void EC2Client::RestoreAddressToClassicAsyncHelper(const RestoreAddressToClassicRequest& request, const RestoreAddressToClassicResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RestoreAddressToClassic(request), context);
}

RevokeSecurityGroupEgressOutcome EC2Client::RevokeSecurityGroupEgress(const RevokeSecurityGroupEgressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RevokeSecurityGroupEgressOutcome(NoResult());
  }
  else
  {
    return RevokeSecurityGroupEgressOutcome(outcome.GetError());
  }
}

RevokeSecurityGroupEgressOutcomeCallable EC2Client::RevokeSecurityGroupEgressCallable(const RevokeSecurityGroupEgressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RevokeSecurityGroupEgress, this, request);
}

void EC2Client::RevokeSecurityGroupEgressAsync(const RevokeSecurityGroupEgressRequest& request, const RevokeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RevokeSecurityGroupEgressAsyncHelper, this, request, handler, context);
}

void EC2Client::RevokeSecurityGroupEgressAsyncHelper(const RevokeSecurityGroupEgressRequest& request, const RevokeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RevokeSecurityGroupEgress(request), context);
}

RevokeSecurityGroupIngressOutcome EC2Client::RevokeSecurityGroupIngress(const RevokeSecurityGroupIngressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RevokeSecurityGroupIngressOutcome(NoResult());
  }
  else
  {
    return RevokeSecurityGroupIngressOutcome(outcome.GetError());
  }
}

RevokeSecurityGroupIngressOutcomeCallable EC2Client::RevokeSecurityGroupIngressCallable(const RevokeSecurityGroupIngressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RevokeSecurityGroupIngress, this, request);
}

void EC2Client::RevokeSecurityGroupIngressAsync(const RevokeSecurityGroupIngressRequest& request, const RevokeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RevokeSecurityGroupIngressAsyncHelper, this, request, handler, context);
}

void EC2Client::RevokeSecurityGroupIngressAsyncHelper(const RevokeSecurityGroupIngressRequest& request, const RevokeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RevokeSecurityGroupIngress(request), context);
}

RunInstancesOutcome EC2Client::RunInstances(const RunInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RunInstancesOutcome(RunInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return RunInstancesOutcome(outcome.GetError());
  }
}

RunInstancesOutcomeCallable EC2Client::RunInstancesCallable(const RunInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RunInstances, this, request);
}

void EC2Client::RunInstancesAsync(const RunInstancesRequest& request, const RunInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RunInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::RunInstancesAsyncHelper(const RunInstancesRequest& request, const RunInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RunInstances(request), context);
}

RunScheduledInstancesOutcome EC2Client::RunScheduledInstances(const RunScheduledInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RunScheduledInstancesOutcome(RunScheduledInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return RunScheduledInstancesOutcome(outcome.GetError());
  }
}

RunScheduledInstancesOutcomeCallable EC2Client::RunScheduledInstancesCallable(const RunScheduledInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::RunScheduledInstances, this, request);
}

void EC2Client::RunScheduledInstancesAsync(const RunScheduledInstancesRequest& request, const RunScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::RunScheduledInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::RunScheduledInstancesAsyncHelper(const RunScheduledInstancesRequest& request, const RunScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RunScheduledInstances(request), context);
}

StartInstancesOutcome EC2Client::StartInstances(const StartInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return StartInstancesOutcome(StartInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return StartInstancesOutcome(outcome.GetError());
  }
}

StartInstancesOutcomeCallable EC2Client::StartInstancesCallable(const StartInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::StartInstances, this, request);
}

void EC2Client::StartInstancesAsync(const StartInstancesRequest& request, const StartInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::StartInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::StartInstancesAsyncHelper(const StartInstancesRequest& request, const StartInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, StartInstances(request), context);
}

StopInstancesOutcome EC2Client::StopInstances(const StopInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return StopInstancesOutcome(StopInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return StopInstancesOutcome(outcome.GetError());
  }
}

StopInstancesOutcomeCallable EC2Client::StopInstancesCallable(const StopInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::StopInstances, this, request);
}

void EC2Client::StopInstancesAsync(const StopInstancesRequest& request, const StopInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::StopInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::StopInstancesAsyncHelper(const StopInstancesRequest& request, const StopInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, StopInstances(request), context);
}

TerminateInstancesOutcome EC2Client::TerminateInstances(const TerminateInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return TerminateInstancesOutcome(TerminateInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return TerminateInstancesOutcome(outcome.GetError());
  }
}

TerminateInstancesOutcomeCallable EC2Client::TerminateInstancesCallable(const TerminateInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::TerminateInstances, this, request);
}

void EC2Client::TerminateInstancesAsync(const TerminateInstancesRequest& request, const TerminateInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::TerminateInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::TerminateInstancesAsyncHelper(const TerminateInstancesRequest& request, const TerminateInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, TerminateInstances(request), context);
}

UnassignPrivateIpAddressesOutcome EC2Client::UnassignPrivateIpAddresses(const UnassignPrivateIpAddressesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UnassignPrivateIpAddressesOutcome(NoResult());
  }
  else
  {
    return UnassignPrivateIpAddressesOutcome(outcome.GetError());
  }
}

UnassignPrivateIpAddressesOutcomeCallable EC2Client::UnassignPrivateIpAddressesCallable(const UnassignPrivateIpAddressesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::UnassignPrivateIpAddresses, this, request);
}

void EC2Client::UnassignPrivateIpAddressesAsync(const UnassignPrivateIpAddressesRequest& request, const UnassignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::UnassignPrivateIpAddressesAsyncHelper, this, request, handler, context);
}

void EC2Client::UnassignPrivateIpAddressesAsyncHelper(const UnassignPrivateIpAddressesRequest& request, const UnassignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UnassignPrivateIpAddresses(request), context);
}

UnmonitorInstancesOutcome EC2Client::UnmonitorInstances(const UnmonitorInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UnmonitorInstancesOutcome(UnmonitorInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return UnmonitorInstancesOutcome(outcome.GetError());
  }
}

UnmonitorInstancesOutcomeCallable EC2Client::UnmonitorInstancesCallable(const UnmonitorInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::UnmonitorInstances, this, request);
}

void EC2Client::UnmonitorInstancesAsync(const UnmonitorInstancesRequest& request, const UnmonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::UnmonitorInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::UnmonitorInstancesAsyncHelper(const UnmonitorInstancesRequest& request, const UnmonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UnmonitorInstances(request), context);
}

