#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "BinaryTree.h"
#include "TreeNode.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    //initialize binary tree
    BinaryTree<int> binaryTree = BinaryTree<int>();
    TreeNode<int>* selectedNode = nullptr;
    int valueBoxValue = 0;
    bool valueBoxEditMode = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

        if (GuiValueBox(Rectangle{ 525, 25, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;

        if (GuiButton(Rectangle{ 660, 25, 125, 30 }, GuiIconText(RICON_OK_TICK, "Insert")))
        {
            // Implement the code to insert valueBoxValue into your binary tree here! 
            binaryTree.insert(valueBoxValue);
            selectedNode = binaryTree.find(valueBoxValue);
        }

        if (GuiButton(Rectangle{ 660, 60, 125, 30 }, GuiIconText(RICON_OK_TICK, "Remove")))
        {
            // Implement the code to remove the node with value = valueBoxValue from your binary tree here! 
            binaryTree.remove(valueBoxValue);
        }

        binaryTree.insert(10);
        binaryTree.insert(5);
        binaryTree.insert(7);
        binaryTree.insert(15);
        binaryTree.insert(12);
        binaryTree.insert(17);
        binaryTree.insert(14);
        binaryTree.remove(15);





        // draw the binary tree
        binaryTree.draw(selectedNode);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}