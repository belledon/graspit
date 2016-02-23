#include <QDir>
#include <iostream>

/**
 * If linking the graspit executable to a static library which
 * holds the Qt resources (particularly for the Pixmaps in the GUI),
 * it is necessary to enforce call of Q_INIT_RESOURCE.
 * This helper class can be used for this - just create a static instance of it
 * in the static library.
 *
 * See also: https://wiki.qt.io/QtResources
 */
class StaticLibInitializer
{
public:
    StaticLibInitializer()
    {
        std::cout<<"YOOOOOOO"<<std::endl;
        initialize();
    }
    ~StaticLibInitializer()
    {
        //qCleanupImages_graspit();
    }
private:
    void initialize()
    {
        //Q_INIT_RESOURCE(qtwidgets_custom_resources);
        //Q_INIT_RESOURCE(graphlib);
        //Q_INIT_RESOURCE(EmbedImage);
        //Q_INIT_RESOURCE(graspit);
        //Q_INIT_RESOURCE(images);
        //qInitImages_graspit();
    }
    //StaticInitImages_graspit staticImages;
};
