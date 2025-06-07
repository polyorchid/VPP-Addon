class FoostsFixes_Core: PluginBase
{
    private FF_ItemBringer m_ItemBringer;
    private FF_DiscoveryExtension m_Discovery;
    private FF_WidgetHookExtension m_WidgetHook;
    
    void FoostsFixes_Core()
    {
        // Initialize our item bringer system
        m_ItemBringer = new FF_ItemBringer();
        
        // Initialize discovery system
        m_Discovery = new FF_DiscoveryExtension();
        
        // Initialize widget hook system
        m_WidgetHook = new FF_WidgetHookExtension();
    }
    
    void ~FoostsFixes_Core()
    {
        delete m_ItemBringer;
        delete m_Discovery;
        delete m_WidgetHook;
    }
    
    override void OnInit()
    {
        super.OnInit();
        
        // Register our plugin with VPP if possible
        Print("[FoostsFixes] Plugin initialized successfully");
        
        // Hook into VPP's ESP system
        GetRPCManager().AddRPC("FoostsFixes", "BringItemToAdmin", this, SingeplayerExecutionType.Both);
    }
    
    // RPC handler for bringing items to admin
    void BringItemToAdmin(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Server)
        {
            Param2<string, vector> data;
            if (!ctx.Read(data))
                return;
                
            string itemClassName = data.param1;
            vector adminPosition = data.param2;
            
            m_ItemBringer.BringItemToPosition(itemClassName, adminPosition, sender);
        }
    }
    
    // Get reference to item bringer for UI
    FF_ItemBringer GetItemBringer()
    {
        return m_ItemBringer;
    }
}

// Global access point
FoostsFixes_Core g_FoostsFixes;