// Alternative approach - hook into ESP widgets without knowing class names
// Place this in: @FoostsFixes/5_Mission/FoostsFixes/Extensions/FF_WidgetHookExtension.c

class FF_WidgetHookExtension
{
    private array<ButtonWidget> m_BringButtons;
    private bool m_HooksInstalled = false;
    
    void FF_WidgetHookExtension()
    {
        m_BringButtons = new array<ButtonWidget>();
        Print("[FoostsFixes] Widget hook extension initialized");
        
        // Check for ESP widgets periodically
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(CheckForESPWidgets, 3000, true);
    }
    
    void ~FF_WidgetHookExtension()
    {
        // Clean up
        for (int i = 0; i < m_BringButtons.Count(); i++)
        {
            if (m_BringButtons[i])
                m_BringButtons[i].Unlink();
        }
        m_BringButtons.Clear();
    }
    
    void CheckForESPWidgets()
    {
        if (m_HooksInstalled)
            return;
            
        // Look for ESP-related widgets by name patterns
        Widget root = GetGame().GetWorkspace();
        if (root)
        {
            SearchAndHookESPWidgets(root);
        }
    }
    
    void SearchAndHookESPWidgets(Widget widget)
    {
        if (!widget)
            return;
            
        string widgetName = widget.GetName();
        
        // Look for ESP item entries or ESP menus
        if (widgetName.Contains("EspItem") || widgetName.Contains("ESP") || 
            widgetName.Contains("Entry") && widgetName.Contains("Esp"))
        {
            AddBringButtonToWidget(widget);
        }
        
        // Search children
        for (int i = 0; i < widget.GetChildren(); i++)
        {
            Widget child = widget.GetChild(i);
            SearchAndHookESPWidgets(child);
        }
    }
    
    void AddBringButtonToWidget(Widget parentWidget)
    {
        // Create a bring button and add it to the ESP widget
        ButtonWidget bringBtn = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("FoostsFixes/GUI/BringItemButton.layout", parentWidget));
        
        if (bringBtn)
        {
            bringBtn.SetText("Bring");
            bringBtn.SetHandler(new FF_BringButtonHandler());
            
            // Position the button
            float x, y;
            parentWidget.GetSize(x, y);
            bringBtn.SetPos(x - 80, 5);
            bringBtn.SetSize(70, 25);
            
            m_BringButtons.Insert(bringBtn);
            
            Print("[FoostsFixes] Added bring button to ESP widget: " + parentWidget.GetName());
        }
    }
}

// Handler for our dynamically created buttons
class FF_BringButtonHandler : ScriptedWidgetEventHandler
{
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (button == MouseState.LEFT)
        {
            OnBringButtonClicked(w);
            return true;
        }
        return false;
    }
    
    void OnBringButtonClicked(Widget buttonWidget)
    {
        Print("[FoostsFixes] Bring button clicked!");
        
        // Try to find the associated ESP object
        Widget parentWidget = buttonWidget.GetParent();
        if (parentWidget)
        {
            // Look for text widgets that might contain item names
            string itemName = FindItemNameInWidget(parentWidget);
            if (itemName != "")
            {
                BringItemByName(itemName);
            }
            else
            {
                Print("[FoostsFixes] Could not determine item name from ESP entry");
            }
        }
    }
    
    string FindItemNameInWidget(Widget widget)
    {
        // Search for text widgets that might contain the item name
        for (int i = 0; i < widget.GetChildren(); i++)
        {
            Widget child = widget.GetChild(i);
            TextWidget textWidget = TextWidget.Cast(child);
            
            if (textWidget)
            {
                string text = textWidget.GetText();
                // Basic filtering - if it looks like an item name
                if (text.Length() > 2 && !text.Contains("[") && !text.Contains("m]"))
                {
                    return text;
                }
            }
            
            // Recursively search children
            string result = FindItemNameInWidget(child);
            if (result != "")
                return result;
        }
        
        return "";
    }
    
    void BringItemByName(string itemName)
    {
        PlayerBase admin = PlayerBase.Cast(GetGame().GetPlayer());
        if (!admin)
            return;
            
        vector adminPos = admin.GetPosition();
        
        // Use our item bringer system
        if (g_FoostsFixes && g_FoostsFixes.GetItemBringer())
        {
            g_FoostsFixes.GetItemBringer().BringItemToPosition(itemName, adminPos, admin.GetIdentity());
            Print("[FoostsFixes] Attempting to bring item: " + itemName);
        }
    }
}