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


DisassociateRouteTableOutcome EC2Client::DisassociateRouteTable(const DisassociateRouteTableRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DisassociateRouteTableOutcome(NoResult());
  }
  else
  {
    return DisassociateRouteTableOutcome(outcome.GetError());
  }
}

DisassociateRouteTableOutcomeCallable EC2Client::DisassociateRouteTableCallable(const DisassociateRouteTableRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::DisassociateRouteTable, this, request);
}

void EC2Client::DisassociateRouteTableAsync(const DisassociateRouteTableRequest& request, const DisassociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::DisassociateRouteTableAsyncHelper, this, request, handler, context);
}

void EC2Client::DisassociateRouteTableAsyncHelper(const DisassociateRouteTableRequest& request, const DisassociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DisassociateRouteTable(request), context);
}

EnableVgwRoutePropagationOutcome EC2Client::EnableVgwRoutePropagation(const EnableVgwRoutePropagationRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return EnableVgwRoutePropagationOutcome(NoResult());
  }
  else
  {
    return EnableVgwRoutePropagationOutcome(outcome.GetError());
  }
}

EnableVgwRoutePropagationOutcomeCallable EC2Client::EnableVgwRoutePropagationCallable(const EnableVgwRoutePropagationRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::EnableVgwRoutePropagation, this, request);
}

void EC2Client::EnableVgwRoutePropagationAsync(const EnableVgwRoutePropagationRequest& request, const EnableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::EnableVgwRoutePropagationAsyncHelper, this, request, handler, context);
}

void EC2Client::EnableVgwRoutePropagationAsyncHelper(const EnableVgwRoutePropagationRequest& request, const EnableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, EnableVgwRoutePropagation(request), context);
}

EnableVolumeIOOutcome EC2Client::EnableVolumeIO(const EnableVolumeIORequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return EnableVolumeIOOutcome(NoResult());
  }
  else
  {
    return EnableVolumeIOOutcome(outcome.GetError());
  }
}

EnableVolumeIOOutcomeCallable EC2Client::EnableVolumeIOCallable(const EnableVolumeIORequest& request) const
{
  return std::async(std::launch::async, &EC2Client::EnableVolumeIO, this, request);
}

void EC2Client::EnableVolumeIOAsync(const EnableVolumeIORequest& request, const EnableVolumeIOResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::EnableVolumeIOAsyncHelper, this, request, handler, context);
}

void EC2Client::EnableVolumeIOAsyncHelper(const EnableVolumeIORequest& request, const EnableVolumeIOResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, EnableVolumeIO(request), context);
}

EnableVpcClassicLinkOutcome EC2Client::EnableVpcClassicLink(const EnableVpcClassicLinkRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return EnableVpcClassicLinkOutcome(EnableVpcClassicLinkResponse(outcome.GetResult()));
  }
  else
  {
    return EnableVpcClassicLinkOutcome(outcome.GetError());
  }
}

EnableVpcClassicLinkOutcomeCallable EC2Client::EnableVpcClassicLinkCallable(const EnableVpcClassicLinkRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::EnableVpcClassicLink, this, request);
}

void EC2Client::EnableVpcClassicLinkAsync(const EnableVpcClassicLinkRequest& request, const EnableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::EnableVpcClassicLinkAsyncHelper, this, request, handler, context);
}

void EC2Client::EnableVpcClassicLinkAsyncHelper(const EnableVpcClassicLinkRequest& request, const EnableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, EnableVpcClassicLink(request), context);
}

EnableVpcClassicLinkDnsSupportOutcome EC2Client::EnableVpcClassicLinkDnsSupport(const EnableVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return EnableVpcClassicLinkDnsSupportOutcome(EnableVpcClassicLinkDnsSupportResponse(outcome.GetResult()));
  }
  else
  {
    return EnableVpcClassicLinkDnsSupportOutcome(outcome.GetError());
  }
}

EnableVpcClassicLinkDnsSupportOutcomeCallable EC2Client::EnableVpcClassicLinkDnsSupportCallable(const EnableVpcClassicLinkDnsSupportRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::EnableVpcClassicLinkDnsSupport, this, request);
}

void EC2Client::EnableVpcClassicLinkDnsSupportAsync(const EnableVpcClassicLinkDnsSupportRequest& request, const EnableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::EnableVpcClassicLinkDnsSupportAsyncHelper, this, request, handler, context);
}

void EC2Client::EnableVpcClassicLinkDnsSupportAsyncHelper(const EnableVpcClassicLinkDnsSupportRequest& request, const EnableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, EnableVpcClassicLinkDnsSupport(request), context);
}

GetConsoleOutputOutcome EC2Client::GetConsoleOutput(const GetConsoleOutputRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GetConsoleOutputOutcome(GetConsoleOutputResponse(outcome.GetResult()));
  }
  else
  {
    return GetConsoleOutputOutcome(outcome.GetError());
  }
}

GetConsoleOutputOutcomeCallable EC2Client::GetConsoleOutputCallable(const GetConsoleOutputRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::GetConsoleOutput, this, request);
}

void EC2Client::GetConsoleOutputAsync(const GetConsoleOutputRequest& request, const GetConsoleOutputResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::GetConsoleOutputAsyncHelper, this, request, handler, context);
}

void EC2Client::GetConsoleOutputAsyncHelper(const GetConsoleOutputRequest& request, const GetConsoleOutputResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetConsoleOutput(request), context);
}

GetPasswordDataOutcome EC2Client::GetPasswordData(const GetPasswordDataRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GetPasswordDataOutcome(GetPasswordDataResponse(outcome.GetResult()));
  }
  else
  {
    return GetPasswordDataOutcome(outcome.GetError());
  }
}

GetPasswordDataOutcomeCallable EC2Client::GetPasswordDataCallable(const GetPasswordDataRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::GetPasswordData, this, request);
}

void EC2Client::GetPasswordDataAsync(const GetPasswordDataRequest& request, const GetPasswordDataResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::GetPasswordDataAsyncHelper, this, request, handler, context);
}

void EC2Client::GetPasswordDataAsyncHelper(const GetPasswordDataRequest& request, const GetPasswordDataResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetPasswordData(request), context);
}

ImportImageOutcome EC2Client::ImportImage(const ImportImageRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ImportImageOutcome(ImportImageResponse(outcome.GetResult()));
  }
  else
  {
    return ImportImageOutcome(outcome.GetError());
  }
}

ImportImageOutcomeCallable EC2Client::ImportImageCallable(const ImportImageRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ImportImage, this, request);
}

void EC2Client::ImportImageAsync(const ImportImageRequest& request, const ImportImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ImportImageAsyncHelper, this, request, handler, context);
}

void EC2Client::ImportImageAsyncHelper(const ImportImageRequest& request, const ImportImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ImportImage(request), context);
}

ImportInstanceOutcome EC2Client::ImportInstance(const ImportInstanceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ImportInstanceOutcome(ImportInstanceResponse(outcome.GetResult()));
  }
  else
  {
    return ImportInstanceOutcome(outcome.GetError());
  }
}

ImportInstanceOutcomeCallable EC2Client::ImportInstanceCallable(const ImportInstanceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ImportInstance, this, request);
}

void EC2Client::ImportInstanceAsync(const ImportInstanceRequest& request, const ImportInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ImportInstanceAsyncHelper, this, request, handler, context);
}

void EC2Client::ImportInstanceAsyncHelper(const ImportInstanceRequest& request, const ImportInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ImportInstance(request), context);
}

ImportKeyPairOutcome EC2Client::ImportKeyPair(const ImportKeyPairRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ImportKeyPairOutcome(ImportKeyPairResponse(outcome.GetResult()));
  }
  else
  {
    return ImportKeyPairOutcome(outcome.GetError());
  }
}

ImportKeyPairOutcomeCallable EC2Client::ImportKeyPairCallable(const ImportKeyPairRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ImportKeyPair, this, request);
}

void EC2Client::ImportKeyPairAsync(const ImportKeyPairRequest& request, const ImportKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ImportKeyPairAsyncHelper, this, request, handler, context);
}

void EC2Client::ImportKeyPairAsyncHelper(const ImportKeyPairRequest& request, const ImportKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ImportKeyPair(request), context);
}

ImportSnapshotOutcome EC2Client::ImportSnapshot(const ImportSnapshotRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ImportSnapshotOutcome(ImportSnapshotResponse(outcome.GetResult()));
  }
  else
  {
    return ImportSnapshotOutcome(outcome.GetError());
  }
}

ImportSnapshotOutcomeCallable EC2Client::ImportSnapshotCallable(const ImportSnapshotRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ImportSnapshot, this, request);
}

void EC2Client::ImportSnapshotAsync(const ImportSnapshotRequest& request, const ImportSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ImportSnapshotAsyncHelper, this, request, handler, context);
}

void EC2Client::ImportSnapshotAsyncHelper(const ImportSnapshotRequest& request, const ImportSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ImportSnapshot(request), context);
}

ImportVolumeOutcome EC2Client::ImportVolume(const ImportVolumeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ImportVolumeOutcome(ImportVolumeResponse(outcome.GetResult()));
  }
  else
  {
    return ImportVolumeOutcome(outcome.GetError());
  }
}

ImportVolumeOutcomeCallable EC2Client::ImportVolumeCallable(const ImportVolumeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ImportVolume, this, request);
}

void EC2Client::ImportVolumeAsync(const ImportVolumeRequest& request, const ImportVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ImportVolumeAsyncHelper, this, request, handler, context);
}

void EC2Client::ImportVolumeAsyncHelper(const ImportVolumeRequest& request, const ImportVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ImportVolume(request), context);
}

ModifyHostsOutcome EC2Client::ModifyHosts(const ModifyHostsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyHostsOutcome(ModifyHostsResponse(outcome.GetResult()));
  }
  else
  {
    return ModifyHostsOutcome(outcome.GetError());
  }
}

ModifyHostsOutcomeCallable EC2Client::ModifyHostsCallable(const ModifyHostsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyHosts, this, request);
}

void EC2Client::ModifyHostsAsync(const ModifyHostsRequest& request, const ModifyHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyHostsAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyHostsAsyncHelper(const ModifyHostsRequest& request, const ModifyHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyHosts(request), context);
}

ModifyIdFormatOutcome EC2Client::ModifyIdFormat(const ModifyIdFormatRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyIdFormatOutcome(NoResult());
  }
  else
  {
    return ModifyIdFormatOutcome(outcome.GetError());
  }
}

ModifyIdFormatOutcomeCallable EC2Client::ModifyIdFormatCallable(const ModifyIdFormatRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyIdFormat, this, request);
}

void EC2Client::ModifyIdFormatAsync(const ModifyIdFormatRequest& request, const ModifyIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyIdFormatAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyIdFormatAsyncHelper(const ModifyIdFormatRequest& request, const ModifyIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyIdFormat(request), context);
}

ModifyImageAttributeOutcome EC2Client::ModifyImageAttribute(const ModifyImageAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyImageAttributeOutcome(NoResult());
  }
  else
  {
    return ModifyImageAttributeOutcome(outcome.GetError());
  }
}

ModifyImageAttributeOutcomeCallable EC2Client::ModifyImageAttributeCallable(const ModifyImageAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyImageAttribute, this, request);
}

void EC2Client::ModifyImageAttributeAsync(const ModifyImageAttributeRequest& request, const ModifyImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyImageAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyImageAttributeAsyncHelper(const ModifyImageAttributeRequest& request, const ModifyImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyImageAttribute(request), context);
}

ModifyInstanceAttributeOutcome EC2Client::ModifyInstanceAttribute(const ModifyInstanceAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyInstanceAttributeOutcome(NoResult());
  }
  else
  {
    return ModifyInstanceAttributeOutcome(outcome.GetError());
  }
}

ModifyInstanceAttributeOutcomeCallable EC2Client::ModifyInstanceAttributeCallable(const ModifyInstanceAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyInstanceAttribute, this, request);
}

void EC2Client::ModifyInstanceAttributeAsync(const ModifyInstanceAttributeRequest& request, const ModifyInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyInstanceAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyInstanceAttributeAsyncHelper(const ModifyInstanceAttributeRequest& request, const ModifyInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyInstanceAttribute(request), context);
}

ModifyInstancePlacementOutcome EC2Client::ModifyInstancePlacement(const ModifyInstancePlacementRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyInstancePlacementOutcome(ModifyInstancePlacementResponse(outcome.GetResult()));
  }
  else
  {
    return ModifyInstancePlacementOutcome(outcome.GetError());
  }
}

ModifyInstancePlacementOutcomeCallable EC2Client::ModifyInstancePlacementCallable(const ModifyInstancePlacementRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyInstancePlacement, this, request);
}

void EC2Client::ModifyInstancePlacementAsync(const ModifyInstancePlacementRequest& request, const ModifyInstancePlacementResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyInstancePlacementAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyInstancePlacementAsyncHelper(const ModifyInstancePlacementRequest& request, const ModifyInstancePlacementResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyInstancePlacement(request), context);
}

ModifyNetworkInterfaceAttributeOutcome EC2Client::ModifyNetworkInterfaceAttribute(const ModifyNetworkInterfaceAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyNetworkInterfaceAttributeOutcome(NoResult());
  }
  else
  {
    return ModifyNetworkInterfaceAttributeOutcome(outcome.GetError());
  }
}

ModifyNetworkInterfaceAttributeOutcomeCallable EC2Client::ModifyNetworkInterfaceAttributeCallable(const ModifyNetworkInterfaceAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyNetworkInterfaceAttribute, this, request);
}

void EC2Client::ModifyNetworkInterfaceAttributeAsync(const ModifyNetworkInterfaceAttributeRequest& request, const ModifyNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyNetworkInterfaceAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyNetworkInterfaceAttributeAsyncHelper(const ModifyNetworkInterfaceAttributeRequest& request, const ModifyNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyNetworkInterfaceAttribute(request), context);
}

ModifyReservedInstancesOutcome EC2Client::ModifyReservedInstances(const ModifyReservedInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyReservedInstancesOutcome(ModifyReservedInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return ModifyReservedInstancesOutcome(outcome.GetError());
  }
}

ModifyReservedInstancesOutcomeCallable EC2Client::ModifyReservedInstancesCallable(const ModifyReservedInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyReservedInstances, this, request);
}

void EC2Client::ModifyReservedInstancesAsync(const ModifyReservedInstancesRequest& request, const ModifyReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyReservedInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyReservedInstancesAsyncHelper(const ModifyReservedInstancesRequest& request, const ModifyReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyReservedInstances(request), context);
}

ModifySnapshotAttributeOutcome EC2Client::ModifySnapshotAttribute(const ModifySnapshotAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifySnapshotAttributeOutcome(NoResult());
  }
  else
  {
    return ModifySnapshotAttributeOutcome(outcome.GetError());
  }
}

ModifySnapshotAttributeOutcomeCallable EC2Client::ModifySnapshotAttributeCallable(const ModifySnapshotAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifySnapshotAttribute, this, request);
}

void EC2Client::ModifySnapshotAttributeAsync(const ModifySnapshotAttributeRequest& request, const ModifySnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifySnapshotAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifySnapshotAttributeAsyncHelper(const ModifySnapshotAttributeRequest& request, const ModifySnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifySnapshotAttribute(request), context);
}

ModifySpotFleetRequestOutcome EC2Client::ModifySpotFleetRequest(const ModifySpotFleetRequestRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifySpotFleetRequestOutcome(ModifySpotFleetRequestResponse(outcome.GetResult()));
  }
  else
  {
    return ModifySpotFleetRequestOutcome(outcome.GetError());
  }
}

ModifySpotFleetRequestOutcomeCallable EC2Client::ModifySpotFleetRequestCallable(const ModifySpotFleetRequestRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifySpotFleetRequest, this, request);
}

void EC2Client::ModifySpotFleetRequestAsync(const ModifySpotFleetRequestRequest& request, const ModifySpotFleetRequestResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifySpotFleetRequestAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifySpotFleetRequestAsyncHelper(const ModifySpotFleetRequestRequest& request, const ModifySpotFleetRequestResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifySpotFleetRequest(request), context);
}

ModifySubnetAttributeOutcome EC2Client::ModifySubnetAttribute(const ModifySubnetAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifySubnetAttributeOutcome(NoResult());
  }
  else
  {
    return ModifySubnetAttributeOutcome(outcome.GetError());
  }
}

ModifySubnetAttributeOutcomeCallable EC2Client::ModifySubnetAttributeCallable(const ModifySubnetAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifySubnetAttribute, this, request);
}

void EC2Client::ModifySubnetAttributeAsync(const ModifySubnetAttributeRequest& request, const ModifySubnetAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifySubnetAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifySubnetAttributeAsyncHelper(const ModifySubnetAttributeRequest& request, const ModifySubnetAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifySubnetAttribute(request), context);
}

ModifyVolumeAttributeOutcome EC2Client::ModifyVolumeAttribute(const ModifyVolumeAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyVolumeAttributeOutcome(NoResult());
  }
  else
  {
    return ModifyVolumeAttributeOutcome(outcome.GetError());
  }
}

ModifyVolumeAttributeOutcomeCallable EC2Client::ModifyVolumeAttributeCallable(const ModifyVolumeAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyVolumeAttribute, this, request);
}

void EC2Client::ModifyVolumeAttributeAsync(const ModifyVolumeAttributeRequest& request, const ModifyVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyVolumeAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyVolumeAttributeAsyncHelper(const ModifyVolumeAttributeRequest& request, const ModifyVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyVolumeAttribute(request), context);
}

ModifyVpcAttributeOutcome EC2Client::ModifyVpcAttribute(const ModifyVpcAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyVpcAttributeOutcome(NoResult());
  }
  else
  {
    return ModifyVpcAttributeOutcome(outcome.GetError());
  }
}

ModifyVpcAttributeOutcomeCallable EC2Client::ModifyVpcAttributeCallable(const ModifyVpcAttributeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyVpcAttribute, this, request);
}

void EC2Client::ModifyVpcAttributeAsync(const ModifyVpcAttributeRequest& request, const ModifyVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyVpcAttributeAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyVpcAttributeAsyncHelper(const ModifyVpcAttributeRequest& request, const ModifyVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyVpcAttribute(request), context);
}

ModifyVpcEndpointOutcome EC2Client::ModifyVpcEndpoint(const ModifyVpcEndpointRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ModifyVpcEndpointOutcome(ModifyVpcEndpointResponse(outcome.GetResult()));
  }
  else
  {
    return ModifyVpcEndpointOutcome(outcome.GetError());
  }
}

ModifyVpcEndpointOutcomeCallable EC2Client::ModifyVpcEndpointCallable(const ModifyVpcEndpointRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ModifyVpcEndpoint, this, request);
}

void EC2Client::ModifyVpcEndpointAsync(const ModifyVpcEndpointRequest& request, const ModifyVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ModifyVpcEndpointAsyncHelper, this, request, handler, context);
}

void EC2Client::ModifyVpcEndpointAsyncHelper(const ModifyVpcEndpointRequest& request, const ModifyVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ModifyVpcEndpoint(request), context);
}

MonitorInstancesOutcome EC2Client::MonitorInstances(const MonitorInstancesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return MonitorInstancesOutcome(MonitorInstancesResponse(outcome.GetResult()));
  }
  else
  {
    return MonitorInstancesOutcome(outcome.GetError());
  }
}

MonitorInstancesOutcomeCallable EC2Client::MonitorInstancesCallable(const MonitorInstancesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::MonitorInstances, this, request);
}

void EC2Client::MonitorInstancesAsync(const MonitorInstancesRequest& request, const MonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::MonitorInstancesAsyncHelper, this, request, handler, context);
}

void EC2Client::MonitorInstancesAsyncHelper(const MonitorInstancesRequest& request, const MonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, MonitorInstances(request), context);
}

MoveAddressToVpcOutcome EC2Client::MoveAddressToVpc(const MoveAddressToVpcRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return MoveAddressToVpcOutcome(MoveAddressToVpcResponse(outcome.GetResult()));
  }
  else
  {
    return MoveAddressToVpcOutcome(outcome.GetError());
  }
}

MoveAddressToVpcOutcomeCallable EC2Client::MoveAddressToVpcCallable(const MoveAddressToVpcRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::MoveAddressToVpc, this, request);
}

void EC2Client::MoveAddressToVpcAsync(const MoveAddressToVpcRequest& request, const MoveAddressToVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::MoveAddressToVpcAsyncHelper, this, request, handler, context);
}

void EC2Client::MoveAddressToVpcAsyncHelper(const MoveAddressToVpcRequest& request, const MoveAddressToVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, MoveAddressToVpc(request), context);
}


