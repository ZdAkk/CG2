#include "freememory.h"
#include "Sheet1/pixeloperations.h"


namespace cg2{
     /**
     * @brief freeMemory free the allocated memory
     * Will be triggered in Imageviewer destructor
     * can be additionally triggered if necessary
     * (To every "new" one "delete")
     */
    void freeMemory()
    {
        delete workingImage;


    }
}
