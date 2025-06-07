// Discovery version - this will help us find VPP's actual class names
// Place this in: @FoostsFixes/5_Mission/FoostsFixes/Extensions/FF_DiscoveryExtension.c

class FF_DiscoveryExtension
{
    void FF_DiscoveryExtension()
    {
        Print("[FoostsFixes] Discovery extension initialized");
        
        // Hook into common widget events to find VPP's ESP classes
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(DiscoverVPPClasses, 5000, false);
    }
    
    void DiscoverVPPClasses()
    {
        Print("[FoostsFixes] Starting VPP class discovery...");
        
        // Look for ESP-related widgets in the UI
        Widget root = GetGame().GetWorkspace();
        if (root)
        {
            FindESPWidgets(root, 0);
        }
    }
    
    void FindESPWidgets(Widget widget, int depth)
    {
        if (!widget || depth > 10) // Prevent infinite recursion
            return;
            
        string widgetName = widget.GetName();
        string className = widget.ClassName();
        
        // Look for ESP-related names
        if (widgetName.Contains("ESP") || widgetName.Contains("Esp") || 
            className.Contains("ESP") || className.Contains("Esp"))
        {
            Print(string.Format("[FoostsFixes] Found ESP widget: Name='%1', Class='%2', Depth=%3", 
                widgetName, className, depth));
        }
        
        // Check children
        for (int i = 0; i < widget.GetChildren(); i++)
        {
            Widget child = widget.GetChild(i);
            FindESPWidgets(child, depth + 1);
        }
    }
}