class CfgMods
{
    class FoostsFixes
    {
        dir = "FoostsFixes";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "FoostsFixes";
        credits = "Foost";
        author = "Foost";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"World", "Mission"};
        
        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"FoostsFixes/4_World"};
            };
            
            class missionScriptModule
            {
                value = "";
                files[] = {"FoostsFixes/5_Mission"};
            };
        };
    };
};