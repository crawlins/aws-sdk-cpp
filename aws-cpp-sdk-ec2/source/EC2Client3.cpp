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


CreateVpcPeeringConnectionOutcome EC2Client::CreateVpcPeeringConnection(const CreateVpcPeeringConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpcPeeringConnectionOutcome(CreateVpcPeeringConnectionResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVpcPeeringConnectionOutcome(outcome.GetError());
  }
}

CreateVpcPeeringConnectionOutcomeCallable EC2Client::CreateVpcPeeringConnectionCallable(const CreateVpcPeeringConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpcPeeringConnection, this, request);
}

void EC2Client::CreateVpcPeeringConnectionAsync(const CreateVpcPeeringConnectionRequest& request, const CreateVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpcPeeringConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpcPeeringConnectionAsyncHelper(const CreateVpcPeeringConnectionRequest& request, const CreateVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpcPeeringConnection(request), context);
}

CreateVpnConnectionOutcome EC2Client::CreateVpnConnection(const CreateVpnConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpnConnectionOutcome(CreateVpnConnectionResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVpnConnectionOutcome(outcome.GetError());
  }
}

CreateVpnConnectionOutcomeCallable EC2Client::CreateVpnConnectionCallable(const CreateVpnConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpnConnection, this, request);
}

void EC2Client::CreateVpnConnectionAsync(const CreateVpnConnectionRequest& request, const CreateVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpnConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpnConnectionAsyncHelper(const CreateVpnConnectionRequest& request, const CreateVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpnConnection(request), context);
}

CreateVpnConnectionRouteOutcome EC2Client::CreateVpnConnectionRoute(const CreateVpnConnectionRouteRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpnConnectionRouteOutcome(NoResult());
  }
  else
  {
    return CreateVpnConnectionRouteOutcome(outcome.GetError());
  }
}

CreateVpnConnectionRouteOutcomeCallable EC2Client::CreateVpnConnectionRouteCallable(const CreateVpnConnectionRouteRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpnConnectionRoute, this, request);
}

void EC2Client::CreateVpnConnectionRouteAsync(const CreateVpnConnectionRouteRequest& request, const CreateVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpnConnectionRouteAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpnConnectionRouteAsyncHelper(const CreateVpnConnectionRouteRequest& request, const CreateVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpnConnectionRoute(request), context);
}

CreateVpnGatewayOutcome EC2Client::CreateVpnGateway(const CreateVpnGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateVpnGatewayOutcome(CreateVpnGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return CreateVpnGatewayOutcome(outcome.GetError());
  }
}

CreateVpnGatewayOutcomeCallable EC2Client::CreateVpnGatewayCallable(const CreateVpnGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CreateVpnGateway, this, request);
}

void EC2Client::CreateVpnGatewayAsync(const CreateVpnGatewayRequest& request, const CreateVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CreateVpnGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::CreateVpnGatewayAsyncHelper(const CreateVpnGatewayRequest& request, const CreateVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateVpnGateway(request), context);
}

DeleteCustomerGatewayOutcome EC2Client::DeleteCustomerGateway(const DeleteCustomerGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteCustomerGatewayOutcome(NoResult());
  }
  else
  {
    return DeleteCustomerGatewayOutcome(outcome.GetError());
  }
}

DeleteCustomerGatewayOutcomeCallable EC2Client::DeleteCustomerGatewayCallable(const DeleteCustomerGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteCustomerGateway, this, request);
}

void EC2Client::DeleteCustomerGatewayAsync(const DeleteCustomerGatewayRequest& request, const DeleteCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteCustomerGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteCustomerGatewayAsyncHelper(const DeleteCustomerGatewayRequest& request, const DeleteCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteCustomerGateway(request), context);
}

DeleteDhcpOptionsOutcome EC2Client::DeleteDhcpOptions(const DeleteDhcpOptionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteDhcpOptionsOutcome(NoResult());
  }
  else
  {
    return DeleteDhcpOptionsOutcome(outcome.GetError());
  }
}

DeleteDhcpOptionsOutcomeCallable EC2Client::DeleteDhcpOptionsCallable(const DeleteDhcpOptionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteDhcpOptions, this, request);
}

void EC2Client::DeleteDhcpOptionsAsync(const DeleteDhcpOptionsRequest& request, const DeleteDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteDhcpOptionsAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteDhcpOptionsAsyncHelper(const DeleteDhcpOptionsRequest& request, const DeleteDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteDhcpOptions(request), context);
}

DeleteFlowLogsOutcome EC2Client::DeleteFlowLogs(const DeleteFlowLogsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteFlowLogsOutcome(DeleteFlowLogsResponse(outcome.GetResult()));
  }
  else
  {
    return DeleteFlowLogsOutcome(outcome.GetError());
  }
}

DeleteFlowLogsOutcomeCallable EC2Client::DeleteFlowLogsCallable(const DeleteFlowLogsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteFlowLogs, this, request);
}

void EC2Client::DeleteFlowLogsAsync(const DeleteFlowLogsRequest& request, const DeleteFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteFlowLogsAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteFlowLogsAsyncHelper(const DeleteFlowLogsRequest& request, const DeleteFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteFlowLogs(request), context);
}

DeleteInternetGatewayOutcome EC2Client::DeleteInternetGateway(const DeleteInternetGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteInternetGatewayOutcome(NoResult());
  }
  else
  {
    return DeleteInternetGatewayOutcome(outcome.GetError());
  }
}

DeleteInternetGatewayOutcomeCallable EC2Client::DeleteInternetGatewayCallable(const DeleteInternetGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteInternetGateway, this, request);
}

void EC2Client::DeleteInternetGatewayAsync(const DeleteInternetGatewayRequest& request, const DeleteInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteInternetGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteInternetGatewayAsyncHelper(const DeleteInternetGatewayRequest& request, const DeleteInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteInternetGateway(request), context);
}

DeleteKeyPairOutcome EC2Client::DeleteKeyPair(const DeleteKeyPairRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteKeyPairOutcome(NoResult());
  }
  else
  {
    return DeleteKeyPairOutcome(outcome.GetError());
  }
}

DeleteKeyPairOutcomeCallable EC2Client::DeleteKeyPairCallable(const DeleteKeyPairRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteKeyPair, this, request);
}

void EC2Client::DeleteKeyPairAsync(const DeleteKeyPairRequest& request, const DeleteKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteKeyPairAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteKeyPairAsyncHelper(const DeleteKeyPairRequest& request, const DeleteKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteKeyPair(request), context);
}

DeleteNatGatewayOutcome EC2Client::DeleteNatGateway(const DeleteNatGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteNatGatewayOutcome(DeleteNatGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return DeleteNatGatewayOutcome(outcome.GetError());
  }
}

DeleteNatGatewayOutcomeCallable EC2Client::DeleteNatGatewayCallable(const DeleteNatGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteNatGateway, this, request);
}

void EC2Client::DeleteNatGatewayAsync(const DeleteNatGatewayRequest& request, const DeleteNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteNatGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteNatGatewayAsyncHelper(const DeleteNatGatewayRequest& request, const DeleteNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteNatGateway(request), context);
}

DeleteNetworkAclOutcome EC2Client::DeleteNetworkAcl(const DeleteNetworkAclRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteNetworkAclOutcome(NoResult());
  }
  else
  {
    return DeleteNetworkAclOutcome(outcome.GetError());
  }
}

DeleteNetworkAclOutcomeCallable EC2Client::DeleteNetworkAclCallable(const DeleteNetworkAclRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteNetworkAcl, this, request);
}

void EC2Client::DeleteNetworkAclAsync(const DeleteNetworkAclRequest& request, const DeleteNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteNetworkAclAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteNetworkAclAsyncHelper(const DeleteNetworkAclRequest& request, const DeleteNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteNetworkAcl(request), context);
}

DeleteNetworkAclEntryOutcome EC2Client::DeleteNetworkAclEntry(const DeleteNetworkAclEntryRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteNetworkAclEntryOutcome(NoResult());
  }
  else
  {
    return DeleteNetworkAclEntryOutcome(outcome.GetError());
  }
}

DeleteNetworkAclEntryOutcomeCallable EC2Client::DeleteNetworkAclEntryCallable(const DeleteNetworkAclEntryRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteNetworkAclEntry, this, request);
}

void EC2Client::DeleteNetworkAclEntryAsync(const DeleteNetworkAclEntryRequest& request, const DeleteNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteNetworkAclEntryAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteNetworkAclEntryAsyncHelper(const DeleteNetworkAclEntryRequest& request, const DeleteNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteNetworkAclEntry(request), context);
}

DeleteNetworkInterfaceOutcome EC2Client::DeleteNetworkInterface(const DeleteNetworkInterfaceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteNetworkInterfaceOutcome(NoResult());
  }
  else
  {
    return DeleteNetworkInterfaceOutcome(outcome.GetError());
  }
}

DeleteNetworkInterfaceOutcomeCallable EC2Client::DeleteNetworkInterfaceCallable(const DeleteNetworkInterfaceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteNetworkInterface, this, request);
}

void EC2Client::DeleteNetworkInterfaceAsync(const DeleteNetworkInterfaceRequest& request, const DeleteNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteNetworkInterfaceAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteNetworkInterfaceAsyncHelper(const DeleteNetworkInterfaceRequest& request, const DeleteNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteNetworkInterface(request), context);
}

DeletePlacementGroupOutcome EC2Client::DeletePlacementGroup(const DeletePlacementGroupRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeletePlacementGroupOutcome(NoResult());
  }
  else
  {
    return DeletePlacementGroupOutcome(outcome.GetError());
  }
}

DeletePlacementGroupOutcomeCallable EC2Client::DeletePlacementGroupCallable(const DeletePlacementGroupRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeletePlacementGroup, this, request);
}

void EC2Client::DeletePlacementGroupAsync(const DeletePlacementGroupRequest& request, const DeletePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeletePlacementGroupAsyncHelper, this, request, handler, context);
}

void EC2Client::DeletePlacementGroupAsyncHelper(const DeletePlacementGroupRequest& request, const DeletePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeletePlacementGroup(request), context);
}

DeleteRouteOutcome EC2Client::DeleteRoute(const DeleteRouteRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteRouteOutcome(NoResult());
  }
  else
  {
    return DeleteRouteOutcome(outcome.GetError());
  }
}

DeleteRouteOutcomeCallable EC2Client::DeleteRouteCallable(const DeleteRouteRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteRoute, this, request);
}

void EC2Client::DeleteRouteAsync(const DeleteRouteRequest& request, const DeleteRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteRouteAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteRouteAsyncHelper(const DeleteRouteRequest& request, const DeleteRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteRoute(request), context);
}

DeleteRouteTableOutcome EC2Client::DeleteRouteTable(const DeleteRouteTableRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteRouteTableOutcome(NoResult());
  }
  else
  {
    return DeleteRouteTableOutcome(outcome.GetError());
  }
}

DeleteRouteTableOutcomeCallable EC2Client::DeleteRouteTableCallable(const DeleteRouteTableRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteRouteTable, this, request);
}

void EC2Client::DeleteRouteTableAsync(const DeleteRouteTableRequest& request, const DeleteRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteRouteTableAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteRouteTableAsyncHelper(const DeleteRouteTableRequest& request, const DeleteRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteRouteTable(request), context);
}

DeleteSecurityGroupOutcome EC2Client::DeleteSecurityGroup(const DeleteSecurityGroupRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteSecurityGroupOutcome(NoResult());
  }
  else
  {
    return DeleteSecurityGroupOutcome(outcome.GetError());
  }
}

DeleteSecurityGroupOutcomeCallable EC2Client::DeleteSecurityGroupCallable(const DeleteSecurityGroupRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteSecurityGroup, this, request);
}

void EC2Client::DeleteSecurityGroupAsync(const DeleteSecurityGroupRequest& request, const DeleteSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteSecurityGroupAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteSecurityGroupAsyncHelper(const DeleteSecurityGroupRequest& request, const DeleteSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSecurityGroup(request), context);
}

DeleteSnapshotOutcome EC2Client::DeleteSnapshot(const DeleteSnapshotRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteSnapshotOutcome(NoResult());
  }
  else
  {
    return DeleteSnapshotOutcome(outcome.GetError());
  }
}

DeleteSnapshotOutcomeCallable EC2Client::DeleteSnapshotCallable(const DeleteSnapshotRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteSnapshot, this, request);
}

void EC2Client::DeleteSnapshotAsync(const DeleteSnapshotRequest& request, const DeleteSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteSnapshotAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteSnapshotAsyncHelper(const DeleteSnapshotRequest& request, const DeleteSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSnapshot(request), context);
}

DeleteSpotDatafeedSubscriptionOutcome EC2Client::DeleteSpotDatafeedSubscription(const DeleteSpotDatafeedSubscriptionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteSpotDatafeedSubscriptionOutcome(NoResult());
  }
  else
  {
    return DeleteSpotDatafeedSubscriptionOutcome(outcome.GetError());
  }
}

DeleteSpotDatafeedSubscriptionOutcomeCallable EC2Client::DeleteSpotDatafeedSubscriptionCallable(const DeleteSpotDatafeedSubscriptionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteSpotDatafeedSubscription, this, request);
}

void EC2Client::DeleteSpotDatafeedSubscriptionAsync(const DeleteSpotDatafeedSubscriptionRequest& request, const DeleteSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteSpotDatafeedSubscriptionAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteSpotDatafeedSubscriptionAsyncHelper(const DeleteSpotDatafeedSubscriptionRequest& request, const DeleteSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSpotDatafeedSubscription(request), context);
}

DeleteSubnetOutcome EC2Client::DeleteSubnet(const DeleteSubnetRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteSubnetOutcome(NoResult());
  }
  else
  {
    return DeleteSubnetOutcome(outcome.GetError());
  }
}

DeleteSubnetOutcomeCallable EC2Client::DeleteSubnetCallable(const DeleteSubnetRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteSubnet, this, request);
}

void EC2Client::DeleteSubnetAsync(const DeleteSubnetRequest& request, const DeleteSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteSubnetAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteSubnetAsyncHelper(const DeleteSubnetRequest& request, const DeleteSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSubnet(request), context);
}

DeleteTagsOutcome EC2Client::DeleteTags(const DeleteTagsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteTagsOutcome(NoResult());
  }
  else
  {
    return DeleteTagsOutcome(outcome.GetError());
  }
}

DeleteTagsOutcomeCallable EC2Client::DeleteTagsCallable(const DeleteTagsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteTags, this, request);
}

void EC2Client::DeleteTagsAsync(const DeleteTagsRequest& request, const DeleteTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteTagsAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteTagsAsyncHelper(const DeleteTagsRequest& request, const DeleteTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteTags(request), context);
}

DeleteVolumeOutcome EC2Client::DeleteVolume(const DeleteVolumeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVolumeOutcome(NoResult());
  }
  else
  {
    return DeleteVolumeOutcome(outcome.GetError());
  }
}

DeleteVolumeOutcomeCallable EC2Client::DeleteVolumeCallable(const DeleteVolumeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVolume, this, request);
}

void EC2Client::DeleteVolumeAsync(const DeleteVolumeRequest& request, const DeleteVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVolumeAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVolumeAsyncHelper(const DeleteVolumeRequest& request, const DeleteVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVolume(request), context);
}

DeleteVpcOutcome EC2Client::DeleteVpc(const DeleteVpcRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVpcOutcome(NoResult());
  }
  else
  {
    return DeleteVpcOutcome(outcome.GetError());
  }
}

DeleteVpcOutcomeCallable EC2Client::DeleteVpcCallable(const DeleteVpcRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVpc, this, request);
}

void EC2Client::DeleteVpcAsync(const DeleteVpcRequest& request, const DeleteVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVpcAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVpcAsyncHelper(const DeleteVpcRequest& request, const DeleteVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVpc(request), context);
}

DeleteVpcEndpointsOutcome EC2Client::DeleteVpcEndpoints(const DeleteVpcEndpointsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVpcEndpointsOutcome(DeleteVpcEndpointsResponse(outcome.GetResult()));
  }
  else
  {
    return DeleteVpcEndpointsOutcome(outcome.GetError());
  }
}

DeleteVpcEndpointsOutcomeCallable EC2Client::DeleteVpcEndpointsCallable(const DeleteVpcEndpointsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVpcEndpoints, this, request);
}

void EC2Client::DeleteVpcEndpointsAsync(const DeleteVpcEndpointsRequest& request, const DeleteVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVpcEndpointsAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVpcEndpointsAsyncHelper(const DeleteVpcEndpointsRequest& request, const DeleteVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVpcEndpoints(request), context);
}

DeleteVpcPeeringConnectionOutcome EC2Client::DeleteVpcPeeringConnection(const DeleteVpcPeeringConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVpcPeeringConnectionOutcome(DeleteVpcPeeringConnectionResponse(outcome.GetResult()));
  }
  else
  {
    return DeleteVpcPeeringConnectionOutcome(outcome.GetError());
  }
}

DeleteVpcPeeringConnectionOutcomeCallable EC2Client::DeleteVpcPeeringConnectionCallable(const DeleteVpcPeeringConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVpcPeeringConnection, this, request);
}

void EC2Client::DeleteVpcPeeringConnectionAsync(const DeleteVpcPeeringConnectionRequest& request, const DeleteVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVpcPeeringConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVpcPeeringConnectionAsyncHelper(const DeleteVpcPeeringConnectionRequest& request, const DeleteVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVpcPeeringConnection(request), context);
}

DeleteVpnConnectionOutcome EC2Client::DeleteVpnConnection(const DeleteVpnConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVpnConnectionOutcome(NoResult());
  }
  else
  {
    return DeleteVpnConnectionOutcome(outcome.GetError());
  }
}

DeleteVpnConnectionOutcomeCallable EC2Client::DeleteVpnConnectionCallable(const DeleteVpnConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVpnConnection, this, request);
}

void EC2Client::DeleteVpnConnectionAsync(const DeleteVpnConnectionRequest& request, const DeleteVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVpnConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVpnConnectionAsyncHelper(const DeleteVpnConnectionRequest& request, const DeleteVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVpnConnection(request), context);
}

DeleteVpnConnectionRouteOutcome EC2Client::DeleteVpnConnectionRoute(const DeleteVpnConnectionRouteRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteVpnConnectionRouteOutcome(NoResult());
  }
  else
  {
    return DeleteVpnConnectionRouteOutcome(outcome.GetError());
  }
}

DeleteVpnConnectionRouteOutcomeCallable EC2Client::DeleteVpnConnectionRouteCallable(const DeleteVpnConnectionRouteRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DeleteVpnConnectionRoute, this, request);
}

void EC2Client::DeleteVpnConnectionRouteAsync(const DeleteVpnConnectionRouteRequest& request, const DeleteVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DeleteVpnConnectionRouteAsyncHelper, this, request, handler, context);
}

void EC2Client::DeleteVpnConnectionRouteAsyncHelper(const DeleteVpnConnectionRouteRequest& request, const DeleteVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteVpnConnectionRoute(request), context);
}

