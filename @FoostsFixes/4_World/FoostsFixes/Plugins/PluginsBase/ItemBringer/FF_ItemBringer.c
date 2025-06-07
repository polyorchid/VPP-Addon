class FF_ItemBringer
{
    void FF_ItemBringer()
    {
        Print("[FoostsFixes] ItemBringer initialized");
    }
    
    // Main function to bring an item to admin position
    void BringItemToPosition(string itemClassName, vector adminPosition, PlayerIdentity adminIdentity)
    {
        if (!GetGame().IsServer())
            return;
            
        // Find the item in the world
        EntityAI targetItem = FindItemByClassName(itemClassName);
        if (!targetItem)
        {
            // Item not found, notify admin
            SendNotificationToAdmin(adminIdentity, "Item not found: " + itemClassName);
            return;
        }
        
        // Calculate safe position near admin (slightly offset to avoid collision)
        vector safePosition = GetSafePositionNearAdmin(adminPosition);
        
        // Move the item
        targetItem.SetPosition(safePosition);
        
        // Notify admin of success
        SendNotificationToAdmin(adminIdentity, "Item brought successfully: " + itemClassName);
        
        Print("[FoostsFixes] Brought item " + itemClassName + " to admin position");
    }
    
    // Find item by class name in the world
    private EntityAI FindItemByClassName(string className)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(vector.Zero, 99999, objects, null);
        
        foreach (Object obj : objects)
        {
            EntityAI item = EntityAI.Cast(obj);
            if (item && item.GetType() == className)
            {
                return item;
            }
        }
        
        return null;
    }
    
    // Calculate safe position near admin
    private vector GetSafePositionNearAdmin(vector adminPos)
    {
        // Offset by 2 meters in front of admin, slightly to the right
        vector offset = Vector(2.0, 0.0, 1.0);
        vector safePos = adminPos + offset;
        
        // Ensure position is on ground
        safePos[1] = GetGame().SurfaceY(safePos[0], safePos[2]);
        
        return safePos;
    }
    
    // Send notification to admin (integrate with VPP notifications if available)
    private void SendNotificationToAdmin(PlayerIdentity adminIdentity, string message)
    {
        PlayerBase admin = PlayerBase.Cast(adminIdentity.GetPlayer());
        if (!admin)
            return;
            
        // Try multiple notification methods for better compatibility
        
        // Method 1: VPP Chat System (if available)
        if (GetVPPUIManager())
        {
            GetVPPUIManager().DisplayNotification(message, "FoostsFixes", 3.0);
        }
        // Method 2: Direct chat message
        else if (GetGame().IsMultiplayer())
        {
            GetGame().ChatMP(admin, message, "colorAction");
        }
        // Method 3: Fallback to action message
        else
        {
            admin.MessageAction("[FoostsFixes] " + message);
        }
        
        // Also log to server console
        Print("[FoostsFixes] " + message + " (Admin: " + adminIdentity.GetName() + ")");
    }
    
    // Alternative method: Bring item by direct reference (for ESP integration)
    void BringSpecificItem(EntityAI item, vector adminPosition, PlayerIdentity adminIdentity)
    {
        if (!GetGame().IsServer() || !item)
            return;
            
        vector safePosition = GetSafePositionNearAdmin(adminPosition);
        item.SetPosition(safePosition);
        
        SendNotificationToAdmin(adminIdentity, "Item brought: " + item.GetDisplayName());
    }
}