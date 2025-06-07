// Alternative approach: Extend the main ESP menu
modded class VPPESPMenu
{
    private ButtonWidget m_BringSelectedButton;
    private Object m_CurrentSelectedObject;
    
    override Widget Init()
    {
        Widget root = super.Init();
        
        // Add our bring button to the ESP menu
        AddBringSelectedButton(root);
        
        return root;
    }
    
    private void AddBringSelectedButton(Widget parent)
    {
        // Find a good spot to add our button (you may need to adjust positioning)
        m_BringSelectedButton = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("FoostsFixes/GUI/BringSelectedButton.layout", parent));
        
        if (m_BringSelectedButton)
        {
            m_BringSelectedButton.SetHandler(this);
            m_BringSelectedButton.SetText("Bring Selected Item");
            m_BringSelectedButton.Enable(false); // Disabled until something is selected
            
            Print("[FoostsFixes] Bring Selected button added to ESP menu");
        }
    }
    
    // Hook into VPP's object selection system
    override void OnESPObjectSelected(Object obj)
    {
        super.OnESPObjectSelected(obj);
        
        m_CurrentSelectedObject = obj;
        
        // Enable/disable our button based on selection and object type
        if (m_BringSelectedButton)
        {
            bool isItem = EntityAI.Cast(obj) != null;
            m_BringSelectedButton.Enable(isItem);
            
            if (isItem)
            {
                EntityAI item = EntityAI.Cast(obj);
                m_BringSelectedButton.SetText("Bring: " + item.GetDisplayName());
            }
            else
            {
                m_BringSelectedButton.SetText("Bring Selected Item");
            }
        }
    }
    
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_BringSelectedButton)
        {
            OnBringSelectedClicked();
            return true;
        }
        
        return super.OnClick(w, x, y, button);
    }
    
    private void OnBringSelectedClicked()
    {
        if (!m_CurrentSelectedObject)
        {
            Print("[FoostsFixes] No object selected");
            return;
        }
        
        EntityAI item = EntityAI.Cast(m_CurrentSelectedObject);
        if (!item)
        {
            Print("[FoostsFixes] Selected object is not an item");
            return;
        }
        
        // Get admin info
        PlayerBase admin = PlayerBase.Cast(GetGame().GetPlayer());
        if (!admin)
        {
            Print("[FoostsFixes] No admin player found");
            return;
        }
        
        vector adminPos = admin.GetPosition();
        
        // Use our item bringer
        if (g_FoostsFixes && g_FoostsFixes.GetItemBringer())
        {
            g_FoostsFixes.GetItemBringer().BringSpecificItem(item, adminPos, admin.GetIdentity());
        }
    }
}