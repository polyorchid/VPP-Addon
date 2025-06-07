class FoostsFixes_Core: PluginBase
{
    private FF_ItemBringer m_ItemBringer;
    private FF_DiscoveryExtension m_Discovery;
    private FF_WidgetHookExtension m_WidgetHook;
    
    void FoostsFixes_Core()
    {
        Print("========================================");
        Print("[FoostsFixes] CORE CONSTRUCTOR CALLED!!!");
        Print("========================================");
        
        // Initialize our item bringer system
        Print("[FoostsFixes] Creating ItemBringer...");
        m_ItemBringer = new FF_ItemBringer();
        
        Print("[FoostsFixes] Creating Discovery extension...");
        m_Discovery = new FF_DiscoveryExtension();
        
        Print("[FoostsFixes] Creating Widget hook extension...");
        m_WidgetHook = new FF_WidgetHookExtension();
        
        Print("[FoostsFixes] All components created successfully");
    }
    
    void ~FoostsFixes_Core()
    {
        Print("[FoostsFixes] Core destructor called");
        delete m_ItemBringer;
        delete m_Discovery;
        delete m_WidgetHook;
    }
    
    override void OnInit()
    {
        Print("========================================");
        Print("[FoostsFixes] CORE OnInit() CALLED!!!");
        Print("========================================");
        
        super.OnInit();
        
        // Register our plugin with VPP if possible
        Print("[FoostsFixes] Plugin initialized successfully");
        
        // Hook into VPP's ESP system
        Print("[FoostsFixes] Registering RPC...");
        GetRPCManager().AddRPC("FoostsFixes", "BringItemToAdmin", this, SingeplayerExecutionType.Both);
        Print("[FoostsFixes] RPC registered successfully");
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

// Global access point with initialization
FoostsFixes_Core g_FoostsFixes;