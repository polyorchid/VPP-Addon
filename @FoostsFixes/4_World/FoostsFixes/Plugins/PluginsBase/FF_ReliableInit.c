// Add this to: @FoostsFixes/4_World/FoostsFixes/Plugins/PluginBase/FF_ReliableInit.c

// Global initialization that runs early
void InitFoostsFixes()
{
    Print("========================================");
    Print("[FoostsFixes] FORCE INITIALIZATION CALLED");
    Print("========================================");
    
    if (!g_FoostsFixes)
    {
        Print("[FoostsFixes] Creating global instance...");
        g_FoostsFixes = new FoostsFixes_Core();
        g_FoostsFixes.OnInit();
        Print("[FoostsFixes] Global instance created successfully");
    }
    else
    {
        Print("[FoostsFixes] Global instance already exists");
    }
}

// Force initialization on world script load
void main()
{
    Print("========================================");
    Print("[FoostsFixes] MAIN() CALLED - FORCE INIT");
    Print("========================================");
    InitFoostsFixes();
}

// Also try to init when game loads
modded class DayZGame
{
    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);
        
        if (eventTypeId == StartupEventTypeID)
        {
            Print("[FoostsFixes] DayZGame startup event - initializing");
            InitFoostsFixes();
        }
    }
}