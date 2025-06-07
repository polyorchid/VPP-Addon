// Create this file: @FoostsFixes/5_Mission/FoostsFixes/FF_MissionInit.c

modded class MissionGameplay
{
    override void OnInit()
    {
        super.OnInit();
        
        // Initialize FoostsFixes when mission starts
        Print("[FoostsFixes] Mission starting, initializing FoostsFixes...");
        InitFoostsFixes();
    }
}

// Alternative initialization if the above doesn't work
modded class MissionServer  
{
    override void OnInit()
    {
        super.OnInit();
        
        // Server-side initialization
        Print("[FoostsFixes] Server mission starting, initializing FoostsFixes...");
        InitFoostsFixes();
    }
}