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
#include <aws/rds/RDS_EXPORTS.h>
#include <aws/rds/RDSRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/memory/stl/AWSVector.h>

namespace Aws
{
namespace RDS
{
namespace Model
{

  /**
   */
  class AWS_RDS_API ModifyDBSnapshotAttributeRequest : public RDSRequest
  {
  public:
    ModifyDBSnapshotAttributeRequest();
    Aws::String SerializePayload() const override;

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline const Aws::String& GetDBSnapshotIdentifier() const{ return m_dBSnapshotIdentifier; }

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline void SetDBSnapshotIdentifier(const Aws::String& value) { m_dBSnapshotIdentifierHasBeenSet = true; m_dBSnapshotIdentifier = value; }

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline void SetDBSnapshotIdentifier(Aws::String&& value) { m_dBSnapshotIdentifierHasBeenSet = true; m_dBSnapshotIdentifier = value; }

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline void SetDBSnapshotIdentifier(const char* value) { m_dBSnapshotIdentifierHasBeenSet = true; m_dBSnapshotIdentifier.assign(value); }

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithDBSnapshotIdentifier(const Aws::String& value) { SetDBSnapshotIdentifier(value); return *this;}

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithDBSnapshotIdentifier(Aws::String&& value) { SetDBSnapshotIdentifier(value); return *this;}

    /**
     * <p>The identifier for the DB snapshot to modify the attributes for.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithDBSnapshotIdentifier(const char* value) { SetDBSnapshotIdentifier(value); return *this;}

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline const Aws::String& GetAttributeName() const{ return m_attributeName; }

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline void SetAttributeName(const Aws::String& value) { m_attributeNameHasBeenSet = true; m_attributeName = value; }

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline void SetAttributeName(Aws::String&& value) { m_attributeNameHasBeenSet = true; m_attributeName = value; }

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline void SetAttributeName(const char* value) { m_attributeNameHasBeenSet = true; m_attributeName.assign(value); }

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithAttributeName(const Aws::String& value) { SetAttributeName(value); return *this;}

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithAttributeName(Aws::String&& value) { SetAttributeName(value); return *this;}

    /**
     * <p>The name of the DB snapshot attribute to modify.</p> <p>To manage
     * authorization for other AWS accounts to copy or restore a manual DB snapshot,
     * this value is <code>restore</code>.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithAttributeName(const char* value) { SetAttributeName(value); return *this;}

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline const Aws::Vector<Aws::String>& GetValuesToAdd() const{ return m_valuesToAdd; }

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline void SetValuesToAdd(const Aws::Vector<Aws::String>& value) { m_valuesToAddHasBeenSet = true; m_valuesToAdd = value; }

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline void SetValuesToAdd(Aws::Vector<Aws::String>&& value) { m_valuesToAddHasBeenSet = true; m_valuesToAdd = value; }

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithValuesToAdd(const Aws::Vector<Aws::String>& value) { SetValuesToAdd(value); return *this;}

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithValuesToAdd(Aws::Vector<Aws::String>&& value) { SetValuesToAdd(value); return *this;}

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToAdd(const Aws::String& value) { m_valuesToAddHasBeenSet = true; m_valuesToAdd.push_back(value); return *this; }

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToAdd(Aws::String&& value) { m_valuesToAddHasBeenSet = true; m_valuesToAdd.push_back(value); return *this; }

    /**
     * <p>A list of DB snapshot attributes to add to the attribute specified by
     * <code>AttributeName</code>.</p> <p>To authorize other AWS Accounts to copy or
     * restore a manual snapshot, this is one or more AWS account identifiers, or
     * <code>all</code> to make the manual DB snapshot restorable by any AWS account.
     * Do not add the <code>all</code> value for any manual DB snapshots that contain
     * private information that you do not want to be available to all AWS
     * accounts.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToAdd(const char* value) { m_valuesToAddHasBeenSet = true; m_valuesToAdd.push_back(value); return *this; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline const Aws::Vector<Aws::String>& GetValuesToRemove() const{ return m_valuesToRemove; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline void SetValuesToRemove(const Aws::Vector<Aws::String>& value) { m_valuesToRemoveHasBeenSet = true; m_valuesToRemove = value; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline void SetValuesToRemove(Aws::Vector<Aws::String>&& value) { m_valuesToRemoveHasBeenSet = true; m_valuesToRemove = value; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithValuesToRemove(const Aws::Vector<Aws::String>& value) { SetValuesToRemove(value); return *this;}

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& WithValuesToRemove(Aws::Vector<Aws::String>&& value) { SetValuesToRemove(value); return *this;}

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToRemove(const Aws::String& value) { m_valuesToRemoveHasBeenSet = true; m_valuesToRemove.push_back(value); return *this; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToRemove(Aws::String&& value) { m_valuesToRemoveHasBeenSet = true; m_valuesToRemove.push_back(value); return *this; }

    /**
     * <p>A list of DB snapshot attributes to remove from the attribute specified by
     * <code>AttributeName</code>.</p> <p>To remove authorization for other AWS
     * Accounts to copy or restore a manual snapshot, this is one or more AWS account
     * identifiers, or <code>all</code> to remove authorization for any AWS account to
     * copy or restore the DB snapshot. If you specify <code>all</code>, AWS accounts
     * that have their account identifier explicitly added to the <code>restore</code>
     * attribute can still copy or restore the manual DB snapshot.</p>
     */
    inline ModifyDBSnapshotAttributeRequest& AddValuesToRemove(const char* value) { m_valuesToRemoveHasBeenSet = true; m_valuesToRemove.push_back(value); return *this; }

  private:
    Aws::String m_dBSnapshotIdentifier;
    bool m_dBSnapshotIdentifierHasBeenSet;
    Aws::String m_attributeName;
    bool m_attributeNameHasBeenSet;
    Aws::Vector<Aws::String> m_valuesToAdd;
    bool m_valuesToAddHasBeenSet;
    Aws::Vector<Aws::String> m_valuesToRemove;
    bool m_valuesToRemoveHasBeenSet;
  };

} // namespace Model
} // namespace RDS
} // namespace Aws
