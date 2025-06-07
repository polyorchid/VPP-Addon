// Add this to: @FoostsFixes/4_World/FoostsFixes/Plugins/PluginBase/FF_SimpleTest.c

// Simple global function that should run when the mod loads
void TestFoostsFixesLoading()
{
    Print("################################################");
    Print("####    FOOSTSFIXES DEFINITELY LOADED      ####");
    Print("####    THIS MESSAGE PROVES MOD WORKS      ####");
    Print("################################################");
}

// Call the test function immediately
class FF_AutoTest
{
    void FF_AutoTest()
    {
        TestFoostsFixesLoading();
        Print("[FoostsFixes] Auto test constructor called");
    }
}

// Create instance to trigger the test
FF_AutoTest g_FoostsFixesTest = new FF_AutoTest();