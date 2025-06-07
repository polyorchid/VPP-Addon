// Create this file: @FoostsFixes/4_World/FoostsFixes/Plugins/PluginBase/FF_Init.c

void InitFoostsFixes()
{
    if (!g_FoostsFixes)
    {
        Print("[FoostsFixes] Initializing global instance...");
        g_FoostsFixes = new FoostsFixes_Core();
        g_FoostsFixes.OnInit();
        Print("[FoostsFixes] Global instance created and initialized");
    }
}