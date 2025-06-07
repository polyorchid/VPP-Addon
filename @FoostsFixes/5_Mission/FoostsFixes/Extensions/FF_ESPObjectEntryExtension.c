// Extend VPP's ESP Object Entry to add our Bring button
modded class ESPObjectEntry
{
    private ButtonWidget m_BringItemButton;
    private bool m_FoostButtonAdded = false;
    
    // Override the initialization to add our button
    override Widget Init()
    {
        Widget root = super.Init();
        
        if (!m_FoostButtonAdded)
        {
            AddBringButton(root);
            m_FoostButtonAdded = true;
        }
        
        return root;
    }
    
    private void AddBringButton(Widget parent)
    {
        // Create bring button widget
        m_BringItemButton = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("FoostsFixes/GUI/BringItemButton.layout", parent));
        
        if (m_BringItemButton)
        {
            m_BringItemButton.SetHandler(this);
            m_BringItemButton.SetText("Bring");
            m_BringItemButton.Show(true);
            
            // Position the button (adjust as needed based on VPP's layout)
            float x, y;
            parent.GetSize(x, y);
            m_BringItemButton.SetPos(x - 80, 5); // Position at right side
            m_BringItemButton.SetSize(70, 25);
            
            Print("[FoostsFixes] Bring button added to ESP item entry");
        }
    }
    
    // Handle our button clicks
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_BringItemButton)
        {
            OnBringItemClicked();
            return true;
        }
        
        return super.OnClick(w, x, y, button);
    }
    
    private void OnBringItemClicked()
    {
        // Get the object this ESP entry represents
        Object espObject = GetESPObject(); // This method should exist in VPP's base class
        EntityAI item = EntityAI.Cast(espObject);
        
        if (!item)
        {
            Print("[FoostsFixes] Selected ESP object is not an item");
            return;
        }
        
        // Get current admin player
        PlayerBase admin = PlayerBase.Cast(GetGame().GetPlayer());
        if (!admin)
        {
            Print("[FoostsFixes] No admin player found");
            return;
        }
        
        // Get admin position
        vector adminPos = admin.GetPosition();
        
        // Call our item bringer system
        if (g_FoostsFixes && g_FoostsFixes.GetItemBringer())
        {
            g_FoostsFixes.GetItemBringer().BringSpecificItem(item, adminPos, admin.GetIdentity());
            Print("[FoostsFixes] Bringing item: " + item.GetDisplayName());
        }
        else
        {
            Print("[FoostsFixes] FoostsFixes core not initialized");
        }
    }
    
    // Alternative approach if GetESPObject() doesn't exist
    private Object GetESPObjectAlternative()
    {
        // If VPP stores the object reference differently, we might need to:
        // 1. Access it through a member variable
        // 2. Get it from the ESP system directly
        // 3. Use the object's position to find it
        
        // This is a fallback - you'll need to check VPP's actual implementation
        return m_Object; // Assuming VPP stores it in m_Object
    }
}