#include "DatabaseManager.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMutexLocker>
#include <QtCore/QTime>
#include <QtCore/QVariant>

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

Q_GLOBAL_STATIC(DatabaseManager, databaseManager)

DatabaseManager::DatabaseManager()
    : mutex(QMutex::Recursive)
{
}

DatabaseManager& DatabaseManager::getInstance()
{
    return *databaseManager();
}

void DatabaseManager::initialize()
{
    QMutexLocker locker(&mutex);

    if (QSqlDatabase::database().tables().count() > 0)
        return;

    QSqlQuery sql;
    sql.exec("CREATE TABLE BlendMode (Id INTEGER PRIMARY KEY, Value TEXT)");
    sql.exec("CREATE TABLE Configuration (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE Chroma (Id INTEGR PRIMARY KEY, Key TEXT)");
    //sql.exec("CREATE TABLE Device (Id INTEGER PRIMARY KEY, Name TEXT, Address TEXT, Port INTEGER, Username TEXT, Password TEXT, Description TEXT, Version TEXT, Shadow TEXT, Channels INTEGER, ChannelFormats TEXT, PreviewChannel INTEGER)");
    sql.exec("CREATE TABLE Device (Id INTEGER PRIMARY KEY, Name TEXT, Address TEXT, Port INTEGER, Username TEXT, Password TEXT, Description TEXT, Version TEXT, Shadow TEXT, Channels INTEGER, ChannelFormats TEXT, PreviewChannel INTEGER, DbUserName TEXT, DbUserPass TEXT)");
    sql.exec("CREATE TABLE Direction (Id INTEGER PRIMARY KEY, Value TEXT)");
    sql.exec("CREATE TABLE Format (Id INTEGER PRIMARY KEY, Name TEXT, Width INTEGER, Height INTEGER, FramesPerSecond TEXT)");
    sql.exec("CREATE TABLE GpiPort (Id INTEGER PRIMARY KEY, RisingEdge INTEGER, Action TEXT)");
    sql.exec("CREATE TABLE GpoPort (Id INTEGER PRIMARY KEY, RisingEdge INTEGER, PulseLengthMillis INTEGER)");
    sql.exec("CREATE TABLE Library (Id INTEGER PRIMARY KEY, Name TEXT, DeviceId INTEGER, TypeId INTEGER, ThumbnailId INTEGER, Timecode TEXT)");
    sql.exec("CREATE TABLE Preset (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE Thumbnail (Id INTEGER PRIMARY KEY, Data TEXT, Timestamp TEXT, Size TEXT)");
    sql.exec("CREATE TABLE Transition (Id INTEGER PRIMARY KEY, Value TEXT)");
    sql.exec("CREATE TABLE Tween (Id INTEGER PRIMARY KEY, Value TEXT)");
    sql.exec("CREATE TABLE Type (Id INTEGER PRIMARY KEY, Value TEXT)");
    sql.exec("CREATE TABLE OscOutput (Id INTEGER PRIMARY KEY, Name TEXT, Address TEXT, Port INTEGER, Description TEXT)");
    sql.exec("CREATE TABLE AtemDevice (Id INTEGER PRIMARY KEY, Name TEXT, Address TEXT, Description TEXT)");
    sql.exec("CREATE TABLE AtemSwitcher (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE AtemStep (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE AtemAutoTransition (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE AtemKeyer (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE AtemVideoFormat (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE AtemAudioInputState (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT)");
    sql.exec("CREATE TABLE TriCasterProduct (Id INTEGER PRIMARY KEY, Name TEXT)");
    sql.exec("CREATE TABLE TriCasterDevice (Id INTEGER PRIMARY KEY, Name TEXT, Address TEXT, Port INTEGER, Description TEXT)");
    sql.exec("CREATE TABLE TriCasterStep (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterInput (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterAutoSpeed (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterAutoTransition (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterPreset (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterSource (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterSwitcher (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");
    sql.exec("CREATE TABLE TriCasterNetworkTarget (Id INTEGER PRIMARY KEY, Name TEXT, Value TEXT, Products TEXT)");

    sql.exec("CREATE TABLE Razuna (Id INTEGER PRIMARY KEY, Name TEXT, apikey TEXT)");

    sql.exec("CREATE TABLE TextScroller (Id INTEGER PRIMARY KEY, news TEXT)");

    sql.exec("INSERT INTO BlendMode (Value) VALUES('Normal')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Lighten')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Darken')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Multiply')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Average')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Add')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Subtract')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Difference')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Negation')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Exclusion')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Screen')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Overlay')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Soft_Light')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Hard_Light')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Color_Dodge ')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Color_Burn')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Linear_Dodge')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Linear_Burn')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Linear_Light')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Vivid_Light')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Pin_Light ')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Hard_Mix')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Reflect')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Glow')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Phoenix')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Contrast')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Saturation')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Color')");
    sql.exec("INSERT INTO BlendMode (Value) VALUES('Luminosity')");

    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('StartFullscreen', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('AutoRefreshLibrary', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ShowThumbnailTooltip', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ReverseOscTime', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('EnableOscInput', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('DisableInAndOutPoints', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('RefreshLibraryInterval', '60')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('GpiSerialPort', 'COM1')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('GpiBaudRate', '115200')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('OscPort', '6250')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('TriCasterPort', '5950')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('DelayType', 'Milliseconds')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('TriCasterProduct', 'TriCaster 8000')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('Theme', 'Flat')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('RundownRepository', '')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('RepositoryPort', '8250')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('PreviewOnAutoStep', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ClearDelayedCommandsOnAutoStep', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ShowAudioLevelsPanel', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ShowPreviewPanel', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ShowLivePanel', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('ShowDurationPanel', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('StoreThumbnailsInDatabase', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('MarkUsedItems', 'false')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('DisableAudioInStream', 'true')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('StreamQuality', '25')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('NetworkCache', '1000')");
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('UseFreezeOnLoad', 'false')");
#if defined(Q_OS_WIN)
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('FontSize', '11')");
#else
    sql.exec("INSERT INTO Configuration (Name, Value) VALUES('FontSize', '12')");
#endif

    sql.exec("INSERT INTO Chroma (Key) VALUES('None')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Red')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Yellow')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Green')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Torquise')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Blue')");
    sql.exec("INSERT INTO Chroma (Key) VALUES('Magenta')");

#if defined(Q_OS_WIN)
    sql.exec("INSERT INTO Device (Name, Address, Port, Username, Password, Description, Version, Shadow, Channels, ChannelFormats, PreviewChannel) VALUES('Local CasparCG', '127.0.0.1', 5250, '', '', '', '', 'No', 0, '', 0)");
#endif

    sql.exec("INSERT INTO Direction (Value) VALUES('RIGHT')");
    sql.exec("INSERT INTO Direction (Value) VALUES('LEFT')");

    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('PAL', 720, 576, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('NTSC', 720, 486, '29.97')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('576p2500', 1024, 576, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p2398', 1280, 720, '23.98')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p2400', 1280, 720, '24')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p2500', 1280, 720, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p5000', 1280, 720, '50')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p2997', 1280, 720, '29.97')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p5994', 1280, 720, '59.94')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p3000', 1280, 720, '30')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('720p6000', 1280, 720, '60')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p2398', 1920, 1080, '23.98')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p2400', 1920, 1080, '24')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080i5000', 1920, 1080, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080i5994', 1920, 1080, '59.94')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080i6000', 1920, 1080, '30')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p2500', 1920, 1080, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p2997', 1920, 1080, '29.97')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p3000', 1920, 1080, '30')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p5000', 1920, 1080, '50')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p5994', 1920, 1080, '59.94')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1080p6000', 1920, 1080, '60')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1556p2398', 2048, 1556, '23.98')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1556p2400', 2048, 1556, '24')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('1556p2500', 2048, 1556, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('2160p2398', 3840, 2160, '23.98')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('2160p2400', 3840, 2160, '24')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('2160p2500', 3840, 2160, '25')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('2160p2997', 3840, 2160, '29.97')");
    sql.exec("INSERT INTO Format (Name, Width, Height, FramesPerSecond) VALUES('2160p3000', 3840, 2160, '30')");

    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(0, 1, 'Stop')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(1, 1, 'Play')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(2, 1, 'Play Now')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(3, 1, 'Pause / Resume')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(4, 1, 'Load')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(5, 1, 'Next')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(6, 1, 'Update')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(7, 1, 'Invoke')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(8, 1, 'Preview')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(9, 1, 'Clear')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(10, 1, 'Clear Video Layer')");
    sql.exec("INSERT INTO GpiPort (Id, RisingEdge, Action) VALUES(11, 1, 'Clear Channel')");

    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(0, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(1, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(2, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(3, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(4, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(5, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(6, 1, 100)");
    sql.exec("INSERT INTO GpoPort (Id, RisingEdge, PulseLengthMillis) VALUES(7, 1, 100)");

    sql.exec("INSERT INTO Transition (Value) VALUES('CUT')");
    sql.exec("INSERT INTO Transition (Value) VALUES('MIX')");
    sql.exec("INSERT INTO Transition (Value) VALUES('PUSH')");
    sql.exec("INSERT INTO Transition (Value) VALUES('SLIDE')");
    sql.exec("INSERT INTO Transition (Value) VALUES('WIPE')");

    sql.exec("INSERT INTO AtemAudioInputState (Name, Value) VALUES('Off', '0')");
    sql.exec("INSERT INTO AtemAudioInputState (Name, Value) VALUES('On', '1')");
    sql.exec("INSERT INTO AtemAudioInputState (Name, Value) VALUES('AFV', '2')");

    sql.exec("INSERT INTO AtemStep (Name, Value) VALUES('Background', 'background')");
    sql.exec("INSERT INTO AtemStep (Name, Value) VALUES('DSK 1', '0')");
    sql.exec("INSERT INTO AtemStep (Name, Value) VALUES('DSK 2', '1')");

    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Downstream Key 1', '0')");
    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Downstream Key 2', '1')");
    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Upstream Key 1', '2')");
    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Upstream Key 2', '3')");
    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Upstream Key 3', '4')");
    sql.exec("INSERT INTO AtemKeyer (Name, Value) VALUES('Upstream Key 4', '5')");

    sql.exec("INSERT INTO AtemAutoTransition (Name, Value) VALUES('MIX', '0')");
    sql.exec("INSERT INTO AtemAutoTransition (Name, Value) VALUES('DIP', '1')");
    sql.exec("INSERT INTO AtemAutoTransition (Name, Value) VALUES('WIPE', '2')");
    sql.exec("INSERT INTO AtemAutoTransition (Name, Value) VALUES('STING', '3')");
    sql.exec("INSERT INTO AtemAutoTransition (Name, Value) VALUES('DVE', '4')");

    sql.exec("INSERT INTO AtemSwitcher (Name, Value) VALUES('Program', 'pgm')");
    sql.exec("INSERT INTO AtemSwitcher (Name, Value) VALUES('Preview', 'prev')");

    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('525 59.94i NTSC', '0')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('625 50i PAL', '1')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('525 59.94i 16:9', '2')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('625 50i 16:9', '3')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('720 50p', '4')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('720 59.94p', '5')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 50i', '6')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 59.94i', '7')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 23.98p', '8')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 24p', '9')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 25p', '10')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 29.97p', '11')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 50p', '12')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('1080 59.94p', '13')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('Ultra HD 23.98p', '14')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('Ultra HD 24p', '15')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('Ultra HD 25p', '16')");
    sql.exec("INSERT INTO AtemVideoFormat (Name, Value) VALUES('Ultra HD 29.97p', '17')");

    sql.exec("INSERT INTO TriCasterProduct (Name) VALUES('TriCaster 410')");
    sql.exec("INSERT INTO TriCasterProduct (Name) VALUES('TriCaster 460')");
    sql.exec("INSERT INTO TriCasterProduct (Name) VALUES('TriCaster 850')");
    sql.exec("INSERT INTO TriCasterProduct (Name) VALUES('TriCaster 860')");
    sql.exec("INSERT INTO TriCasterProduct (Name) VALUES('TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('Background', 'background', 'TriCaster 850')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('Background', 'main_background', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 1', 'overlay0', 'TriCaster 850')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 2', 'overlay1', 'TriCaster 850')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 1', 'main_dsk1', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 2', 'main_dsk2', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 3', 'main_dsk3', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterStep (Name, Value, Products) VALUES('DSK 4', 'main_dsk4', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('DDR 1', 'ddr', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('DDR 2', 'ddr2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Net 1', 'net', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Net 2', 'net2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Still', 'stills', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Title', 'titles', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Frame Buffer', 'frm bfr', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Black', 'black', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 1', 'input1', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 2', 'input2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 3', 'input3', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 4', 'input4', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 5', 'input5', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 6', 'input6', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 7', 'input7', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Input 8', 'input8', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 1', 'v1', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 2', 'v2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 3', 'v3', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 4', 'v4', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 5', 'v5', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 6', 'v6', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 7', 'v7', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterInput (Name, Value, Products) VALUES('Virtual Input 8', 'v8', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterAutoSpeed (Name, Value, Products) VALUES('Default', '', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoSpeed (Name, Value, Products) VALUES('Slow', 'slow', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoSpeed (Name, Value, Products) VALUES('Medium', 'medium', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoSpeed (Name, Value, Products) VALUES('Fast', 'fast', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Default', '', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 1', '0', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 2', '1', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 3', '2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 4', '3', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 5', '4', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 6', '5', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterAutoTransition (Name, Value, Products) VALUES('Preset 7', '6', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 1', '0', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 2', '1', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 3', '2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 4', '3', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 5', '4', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 6', '5', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 7', '6', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 8', '7', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 9', '8', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 10', '9', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 11', '10', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 12', '11', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 13', '12', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 14', '13', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterPreset (Name, Value, Products) VALUES('Preset 15', '14', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Switcher', 'main', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('DDR 1', 'ddr', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('DDR 2', 'ddr2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Still', 'stills', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Title', 'titles', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Sound', 'sound', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Audiomixer', 'audiomixer', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 1', 'v1', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 2', 'v2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 3', 'v3', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 4', 'v4', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 5', 'v5', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 6', 'v6', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 7', 'v7', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('Virtual Input 8', 'v8', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 1', 'ptz_input1', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 2', 'ptz_input2', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 3', 'ptz_input3', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 4', 'ptz_input4', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 5', 'ptz_input5', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 6', 'ptz_input6', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 7', 'ptz_input7', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSource (Name, Value, Products) VALUES('PTZ 8', 'ptz_input8', 'TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterSwitcher (Name, Value, Products) VALUES('Program', 'pgm', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterSwitcher (Name, Value, Products) VALUES('Preview', 'prev', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO TriCasterNetworkTarget (Name, Value, Products) VALUES('Net 1', 'net', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");
    sql.exec("INSERT INTO TriCasterNetworkTarget (Name, Value, Products) VALUES('Net 2', 'net2', 'TriCaster 850, TriCaster 410, TriCaster 460, TriCaster 860, TriCaster 8000')");

    sql.exec("INSERT INTO Tween (Value) VALUES('Linear')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseNone')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInQuad')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutQuad')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutQuad')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInQuad')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInCubic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutCubic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutCubic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInCubic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInQuart')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutQuart')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutQuart')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInQuart')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInQuint')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutQuint')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutQuint')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInQuint')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInSine')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutSine')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutSine')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInSine')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInExpo')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutExpo')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutExpo')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInExpo')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInCirc')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutCirc')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutCirc')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInCirc')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInElastic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutElastic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutElastic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInElastic')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInBack')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutBack')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutBack')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInBack')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutBounce')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInBounce')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseInOutBounce')");
    sql.exec("INSERT INTO Tween (Value) VALUES('EaseOutInBounce')");

    sql.exec("INSERT INTO Type (Value) VALUES('AUDIO')");
    sql.exec("INSERT INTO Type (Value) VALUES('DATA')");
    sql.exec("INSERT INTO Type (Value) VALUES('MOVIE')");
    sql.exec("INSERT INTO Type (Value) VALUES('STILL')");
    sql.exec("INSERT INTO Type (Value) VALUES('TEMPLATE')");
}

void DatabaseManager::uninitialize()
{
}

void DatabaseManager::updateConfiguration(const ConfigurationModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE Configuration SET Value = '%1' "
                            "WHERE Name = '%2'").arg(model.getValue()).arg(model.getName());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

ConfigurationModel DatabaseManager::getConfigurationByName(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT c.Id, c.Name, c.Value FROM Configuration c "
                            "WHERE c.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return ConfigurationModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString());
}

QList<FormatModel> DatabaseManager::getFormat()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT f.Id, f.Name, f.Width, f.Height, f.FramesPerSecond FROM Format f");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<FormatModel> models;
    while (sql.next())
        models.push_back(FormatModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toInt(), sql.value(3).toInt(), sql.value(4).toString()));

    return models;
}

FormatModel DatabaseManager::getFormat(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT f.Id, f.Name, f.Width, f.Height, f.FramesPerSecond FROM Format f "
                            "WHERE f.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return FormatModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toInt(), sql.value(3).toInt(), sql.value(4).toString());
}

QList<PresetModel> DatabaseManager::getPreset()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT p.Id, p.Name, p.Value FROM Preset p");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<PresetModel> models;
    while (sql.next())
        models.push_back(PresetModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

PresetModel DatabaseManager::getPreset(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT p.Id, p.Name, p.Value FROM Preset p "
                            "WHERE p.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return PresetModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString());
}

QList<PresetModel> DatabaseManager::getPresetByFilter(const QString& filter)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT p.Id, p.Name, p.Value "
                            "WHERE p.Name LIKE '%%1%' OR p.Value LIKE '%%1%' "
                            "ORDER BY p.Name, p.Id").arg(filter);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<PresetModel> models;
    while (sql.next())
        models.push_back(PresetModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

void DatabaseManager::insertPreset(const PresetModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO Preset (Name, Value) "
                            "VALUES('%1', '%2')").arg(model.getName()).arg(model.getValue());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::deletePreset(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM Preset WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<BlendModeModel> DatabaseManager::getBlendMode()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT b.Id, b.Value FROM BlendMode b");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<BlendModeModel> models;
    while (sql.next())
        models.push_back(BlendModeModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<ChromaModel> DatabaseManager::getChroma()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT c.Id, c.Key FROM Chroma c");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<ChromaModel> models;
    while (sql.next())
        models.push_back(ChromaModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<DirectionModel> DatabaseManager::getDirection()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT d.Id, d.Value FROM Direction d");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<DirectionModel> models;
    while (sql.next())
        models.push_back(DirectionModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<TransitionModel> DatabaseManager::getTransition()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT t.Id, t.Value FROM Transition t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TransitionModel> models;
    while (sql.next())
        models.push_back(TransitionModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<TweenModel> DatabaseManager::getTween()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT t.Id, t.Value FROM Tween t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TweenModel> models;
    while (sql.next())
        models.push_back(TweenModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<OscOutputModel> DatabaseManager::getOscOutput()
{
    QString query("SELECT o.Id, o.Name, o.Address, o.Port, o.Description FROM OscOutput o "
                  "ORDER BY o.Name");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<OscOutputModel> models;
    while (sql.next())
        models.push_back(OscOutputModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                                        sql.value(3).toInt(), sql.value(4).toString()));

    return models;
}

void DatabaseManager::insertOscOutput(const OscOutputModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO OscOutput (Name, Address, Port, Description) "
                            "VALUES('%1', '%2', %3, '%4')")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getDescription());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

OscOutputModel DatabaseManager::getOscOutputByName(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT o.Id, o.Name, o.Address, o.Port, o.Description FROM OscOutput o "
                            "WHERE o.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return OscOutputModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                          sql.value(3).toInt(), sql.value(4).toString());
}

OscOutputModel DatabaseManager::getOscOutputByAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT o.Id, o.Name, o.Address, o.Port, o.Description FROM OscOutput o "
                            "WHERE o.Address = '%1'").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return OscOutputModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                          sql.value(3).toInt(), sql.value(4).toString());
}

void DatabaseManager::updateOscOutput(const OscOutputModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE OscOutput SET Name = '%1', Address = '%2', Port = %3, Description = '%4' WHERE Id = %5")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getDescription()).arg(model.getId());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteOscOutput(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM OscOutput WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<AtemStepModel> DatabaseManager::getAtemStep()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemStep t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemStepModel> models;
    while (sql.next())
        models.push_back(AtemStepModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemAudioInputStateModel> DatabaseManager::getAtemAudioInputState()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemAudioInputState t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemAudioInputStateModel> models;
    while (sql.next())
        models.push_back(AtemAudioInputStateModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemKeyerModel> DatabaseManager::getAtemKeyer()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemKeyer t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemKeyerModel> models;
    while (sql.next())
        models.push_back(AtemKeyerModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemSwitcherModel> DatabaseManager::getAtemSwitcher()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemSwitcher t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemSwitcherModel> models;
    while (sql.next())
        models.push_back(AtemSwitcherModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemVideoFormatModel> DatabaseManager::getAtemVideoFormat()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemVideoFormat t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemVideoFormatModel> models;
    while (sql.next())
        models.push_back(AtemVideoFormatModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemAutoTransitionModel> DatabaseManager::getAtemAutoTransition()
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Name, t.Value FROM AtemAutoTransition t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemAutoTransitionModel> models;
    while (sql.next())
        models.push_back(AtemAutoTransitionModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<AtemDeviceModel> DatabaseManager::getAtemDevice()
{
    QString query("SELECT o.Id, o.Name, o.Address, o.Description FROM AtemDevice o "
                  "ORDER BY o.Name");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<AtemDeviceModel> models;
    while (sql.next())
        models.push_back(AtemDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

AtemDeviceModel DatabaseManager::getAtemDeviceByName(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Description FROM AtemDevice d "
                            "WHERE d.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return AtemDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString());
}

AtemDeviceModel DatabaseManager::getAtemDeviceByAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Description FROM AtemDevice d "
                            "WHERE d.Address = '%1'").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return AtemDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString());
}

void DatabaseManager::insertAtemDevice(const AtemDeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO AtemDevice (Name, Address, Description) "
                            "VALUES('%1', '%2', '%3')")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getDescription());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateAtemDevice(const AtemDeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE AtemDevice SET Name = '%1', Address = '%2', Description = '%3' WHERE Id = %4")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getDescription()).arg(model.getId());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteAtemDevice(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM AtemDevice WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<TriCasterProductModel> DatabaseManager::getTriCasterProduct()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT p.Id, p.Name FROM TriCasterProduct p");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterProductModel> models;
    while (sql.next())
        models.push_back(TriCasterProductModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

QList<TriCasterInputModel> DatabaseManager::getTriCasterInput()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterInput t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterInputModel> models;
    while (sql.next())
        models.push_back(TriCasterInputModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

QList<TriCasterStepModel> DatabaseManager::getTriCasterStep()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterStep t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterStepModel> models;
    while (sql.next())
        models.push_back(TriCasterStepModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterAutoSpeedModel> DatabaseManager::getTriCasterAutoSpeed()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterAutoSpeed t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterAutoSpeedModel> models;
    while (sql.next())
        models.push_back(TriCasterAutoSpeedModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterAutoTransitionModel> DatabaseManager::getTriCasterAutoTransition()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterAutoTransition t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterAutoTransitionModel> models;
    while (sql.next())
        models.push_back(TriCasterAutoTransitionModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterPresetModel> DatabaseManager::getTriCasterPreset()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterPreset t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterPresetModel> models;
    while (sql.next())
        models.push_back(TriCasterPresetModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterSourceModel> DatabaseManager::getTriCasterSource()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterSource t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterSourceModel> models;
    while (sql.next())
        models.push_back(TriCasterSourceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterSwitcherModel> DatabaseManager::getTriCasterSwitcher()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterSwitcher t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterSwitcherModel> models;
    while (sql.next())
        models.push_back(TriCasterSwitcherModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterNetworkTargetModel> DatabaseManager::getTriCasterNetworkTarget()
{
    QMutexLocker locker(&mutex);

    QString product = getConfigurationByName("TriCasterProduct").getValue();
    QString query = QString("SELECT t.Id, t.Name, t.Value, t.Products FROM TriCasterNetworkTarget t "
                            "WHERE t.Products LIKE '%%1%'").arg(product);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterNetworkTargetModel> models;
    while (sql.next())
        models.push_back(TriCasterNetworkTargetModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString()));

    return models;
}

QList<TriCasterDeviceModel> DatabaseManager::getTriCasterDevice()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT d.Id, d.Name, d.Address, d.Port, d.Description FROM TriCasterDevice d "
                  "ORDER BY d.Name");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TriCasterDeviceModel> models;
    while (sql.next())
        models.push_back(TriCasterDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                                              sql.value(3).toInt(), sql.value(4).toString()));

    return models;
}

TriCasterDeviceModel DatabaseManager::getTriCasterDeviceByName(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Port, d.Description FROM TriCasterDevice d "
                            "WHERE d.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return TriCasterDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                                sql.value(3).toInt(), sql.value(4).toString());
}

TriCasterDeviceModel DatabaseManager::getTriCasterDeviceByAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Port, d.Description FROM TriCasterDevice d "
                            "WHERE d.Address = '%1'").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return TriCasterDeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                                sql.value(3).toInt(), sql.value(4).toString());
}

void DatabaseManager::insertTriCasterDevice(const TriCasterDeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO TriCasterDevice (Name, Address, Port, Description) "
                            "VALUES('%1', '%2', %3, '%4')")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getDescription());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateTriCasterDevice(const TriCasterDeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE TriCasterDevice SET Name = '%1', Address = '%2', Port = %3, Description = '%4' WHERE Id = %5")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getDescription()).arg(model.getId());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteTriCasterDevice(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM TriCasterDevice WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<GpiPortModel> DatabaseManager::getGpiPorts()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT Id, RisingEdge, Action FROM GpiPort ORDER BY Id");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<GpiPortModel> models;
    while (sql.next())
        models.push_back(GpiPortModel(sql.value(0).toInt(), sql.value(1).toInt() == 1, Playout::fromString(sql.value(2).toString())));

    return models;
}

void DatabaseManager::updateGpiPort(const GpiPortModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE GpiPort SET Action = '%1', RisingEdge = %2 "
                            "WHERE Id = %3").arg(Playout::toString(model.getAction())).arg(model.isRisingEdge() ? "1" : "0").arg(model.getPort());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<GpoPortModel> DatabaseManager::getGpoPorts()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT Id, RisingEdge, PulseLengthMillis "
                  "FROM GpoPort ORDER BY Id");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<GpoPortModel> models;
    while (sql.next())
        models.push_back(GpoPortModel(sql.value(0).toInt(), sql.value(1).toInt() == 1, sql.value(2).toInt()));

    return models;
}

void DatabaseManager::updateGpoPort(const GpoPortModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE GpoPort SET PulseLengthMillis = %1, RisingEdge = %2 "
                            "WHERE Id = %3").arg(model.getPulseLengthMillis()).arg(model.isRisingEdge() ? "1" : "0").arg(model.getPort());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<TypeModel> DatabaseManager::getType()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT t.Id, t.Value FROM Type t");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<TypeModel> models;
    while (sql.next())
        models.push_back(TypeModel(sql.value(0).toInt(), sql.value(1).toString()));

    return models;
}

TypeModel DatabaseManager::getTypeByValue(const QString& value)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id FROM Type t "
                            "WHERE t.Value = '%1'").arg(value);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return TypeModel(sql.value(0).toInt(), sql.value(1).toString());
}

QList<DeviceModel> DatabaseManager::getDevice()
{
    QString query("SELECT d.Id, d.Name, d.Address, d.Port, d.Username, d.Password, d.Description, d.Version, d.Shadow, d.Channels, d.ChannelFormats, d.PreviewChannel FROM Device d "
                  "ORDER BY d.Name");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<DeviceModel> models;
    while (sql.next())
        models.push_back(DeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toInt(),
                                     sql.value(4).toString(), sql.value(5).toString(), sql.value(6).toString(), sql.value(7).toString(),
                                     sql.value(8).toString(), sql.value(9).toInt(), sql.value(10).toString(), sql.value(11).toInt(),sql.value(12).toString(),sql.value(13).toString()));

    return models;
}

DeviceModel DatabaseManager::getDeviceByName(const QString& name)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Port, d.Username, d.Password, d.Description, d.Version, d.Shadow, d.Channels, d.ChannelFormats, d.PreviewChannel FROM Device d "
                            "WHERE d.Name = '%1'").arg(name);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return DeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toInt(),
                       sql.value(4).toString(), sql.value(5).toString(), sql.value(6).toString(), sql.value(6).toString(),
                       sql.value(8).toString(), sql.value(9).toInt(), sql.value(10).toString(), sql.value(11).toInt(),sql.value(12).toString(),sql.value(13).toString());
}

DeviceModel DatabaseManager::getDeviceByAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT d.Id, d.Name, d.Address, d.Port, d.Username, d.Password, d.Description, d.Version, d.Shadow, d.Channels, d.ChannelFormats, d.PreviewChannel FROM Device d "
                            "WHERE d.Address = '%1'").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return DeviceModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toInt(),
                       sql.value(4).toString(), sql.value(5).toString(), sql.value(6).toString(), sql.value(6).toString(),
                       sql.value(8).toString(), sql.value(9).toInt(), sql.value(10).toString(), sql.value(11).toInt(),sql.value(12).toString(),sql.value(13).toString());
}

void DatabaseManager::insertDevice(const DeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO Device (Name, Address, Port, Username, Password, Description, Version, Shadow, Channels, ChannelFormats, PreviewChannel, DbUserName, DbUserPass) "
                            "VALUES('%1', '%2', %3, '%4', '%5', '%6', '%7', '%8', %9, '%10', %11, '%12', '%13')")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getUsername())
                            .arg(model.getPassword()).arg(model.getDescription()).arg(model.getVersion()).arg(model.getShadow())
            .arg(model.getChannels()).arg(model.getChannelFormats()).arg(model.getPreviewChannel()).arg(model.getDbUserName()).arg(model.getDbUserPass());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateDevice(const DeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE Device SET Name = '%1', Address = '%2', Port = %3, Username = '%4', Password = '%5', Description = '%6', Version = '%7', Shadow = '%8', Channels = %9, ChannelFormats = '%10', PreviewChannel = %11 "
                            "WHERE Id = %12")
                            .arg(model.getName()).arg(model.getAddress()).arg(model.getPort()).arg(model.getUsername())
                            .arg(model.getPassword()).arg(model.getDescription()).arg(model.getVersion()).arg(model.getShadow())
                            .arg(model.getChannels()).arg(model.getChannelFormats()).arg(model.getPreviewChannel())
                            .arg(model.getId());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateDeviceVersion(const DeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE Device SET Version = '%1' "
                            "WHERE Address = '%2'").arg(model.getVersion()).arg(model.getAddress());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateDeviceChannels(const DeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE Device SET Channels = %1 "
                            "WHERE Address = '%2'").arg(model.getChannels()).arg(model.getAddress());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateDeviceChannelFormats(const DeviceModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE Device SET ChannelFormats = '%1' "
                            "WHERE Address = '%2'").arg(model.getChannelFormats()).arg(model.getAddress());

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteDevice(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM Device WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    query = QString("DELETE FROM Thumbnail WHERE Id IN (SELECT l.ThumbnailId FROM Library l WHERE DeviceId = %1)").arg(id);

    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    query = QString("DELETE FROM Library WHERE DeviceId = %1").arg(id);

    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<LibraryModel> DatabaseManager::getLibraryMedia()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                  "WHERE  l.DeviceId = d.Id AND l.TypeId = t.Id AND (l.TypeId = 1 OR l.TypeId = 3 OR l.TypeId = 4) "
                  "ORDER BY l.Name, l.DeviceId");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryTemplate()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                  "WHERE  l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 5 "
                  "ORDER BY l.Name, l.DeviceId");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryData()
{
    QMutexLocker locker(&mutex);

    QString query("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                  "WHERE  l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 2 "
                  "ORDER BY l.Name, l.DeviceId");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryMediaByFilter(const QString& filter, QList<QString> devices)
{
    QMutexLocker locker(&mutex);

    QString query;

    if (!filter.isEmpty() && devices.isEmpty()) // Filter on all devices.
    {
        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND (l.TypeId = 1 OR l.TypeId = 3 OR l.TypeId = 4) AND l.Name LIKE '%%1%' "
                        "ORDER BY l.Name, l.DeviceId").arg(filter);
    }
    else if (!filter.isEmpty() && !devices.isEmpty()) // Filter specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND (l.TypeId = 1 OR l.TypeId = 3 OR l.TypeId = 4) AND l.Name LIKE '%%1%' AND (%2) "
                        "ORDER BY l.Name, l.DeviceId").arg(filter).arg(address);
    }
    else if (filter.isEmpty() && !devices.isEmpty()) // All on specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND (l.TypeId = 1 OR l.TypeId = 3 OR l.TypeId = 4) AND (%1) "
                        "ORDER BY l.Name, l.DeviceId").arg(address);
    }

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryTemplateByFilter(const QString& filter, QList<QString> devices)
{
    QMutexLocker locker(&mutex);

    QString query;

    if (!filter.isEmpty() && devices.isEmpty()) // Filter on all devices.
    {
        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 5 AND l.Name LIKE '%%1%' "
                        "ORDER BY l.Name, l.DeviceId").arg(filter);
    }
    else if (!filter.isEmpty() && !devices.isEmpty()) // Filter specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 5 AND l.Name LIKE '%%1%' AND (%2) "
                        "ORDER BY l.Name, l.DeviceId").arg(filter).arg(address);
    }
    else if (filter.isEmpty() && !devices.isEmpty()) // All on specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 5 AND (%1) "
                        "ORDER BY l.Name, l.DeviceId").arg(address);
    }

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryDataByFilter(const QString& filter, QList<QString> devices)
{
    QMutexLocker locker(&mutex);

    QString query;

    if (!filter.isEmpty() && devices.isEmpty()) // Filter on all devices.
    {
        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 2 AND l.Name LIKE '%%1%' "
                        "ORDER BY l.Name, l.DeviceId").arg(filter);
    }
    else if (!filter.isEmpty() && !devices.isEmpty()) // Filter specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 2 AND l.Name LIKE '%%1%' AND (%2) "
                        "ORDER BY l.Name, l.DeviceId").arg(filter).arg(address);
    }
    else if (filter.isEmpty() && !devices.isEmpty()) // All on specific devices.
    {
        QString address;
        foreach (QString device, devices)
            address += QString("d.Address LIKE '%%1%' OR ").arg(device);

        address = address.mid(0, address.length() - 4); // Remove the last OR.

        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 2 AND (%1) "
                        "ORDER BY l.Name, l.DeviceId").arg(address);
    }

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryByDeviceId(int deviceId)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                            "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND d.Id = %1 "
                            "ORDER BY l.Name, l.DeviceId").arg(deviceId);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryByDeviceIdAndFilter(int deviceId, const QString& filter)
{
    QMutexLocker locker(&mutex);

    QString query;

    if (filter.isEmpty())
    {
        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND d.Id = %1 "
                        "ORDER BY l.Name, l.DeviceId").arg(deviceId);
    }
    else // Filter.
    {
        query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                        "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND d.Id = %1 AND l.Name LIKE '%%2%' "
                        "ORDER BY l.Name, l.DeviceId").arg(deviceId).arg(filter);
    }

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryMediaByDeviceAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                            "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND (l.TypeId = 1 OR l.TypeId = 3 OR l.TypeId = 4) AND d.Address = '%1' "
                            "ORDER BY l.Id, l.DeviceId").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryTemplateByDeviceAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                            "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 5 AND d.Address = '%1' "
                            "ORDER BY l.Id, l.DeviceId").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryDataByDeviceAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                            "WHERE l.DeviceId = d.Id AND l.TypeId = t.Id AND l.TypeId = 2 AND d.Address = '%1' "
                            "ORDER BY l.Id, l.DeviceId").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

QList<LibraryModel> DatabaseManager::getLibraryByNameAndDeviceId(const QString& name, int deviceId)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT l.Id, l.Name, d.Name, t.Value, l.ThumbnailId, l.Timecode FROM Library l, Device d, Type t "
                            "WHERE  l.Name = '%1' AND l.DeviceId = %2 AND l.DeviceId = d.Id AND l.TypeId = t.Id")
                            .arg(name).arg(deviceId);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<LibraryModel> models;
    while (sql.next())
        models.push_back(LibraryModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(1).toString(),
                                      sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toInt(),
                                      sql.value(5).toString()));

    return models;
}

void DatabaseManager::updateLibraryMedia(const QString& address, const QList<LibraryModel>& deleteModels, const QList<LibraryModel>& insertModels)
{
    QMutexLocker locker(&mutex);

    int deviceId = getDeviceByAddress(address).getId();
    QList<TypeModel> typeModels = getType();

    QSqlDatabase::database().transaction();

    QSqlQuery sql;
    if (deleteModels.count() > 0)
    {
        for (int i = 0; i < deleteModels.count(); i++)
        {
            QString query = QString("DELETE FROM Library WHERE Id = %1").arg(deleteModels.at(i).getId());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    if (insertModels.count() > 0)
    {
        int typeId;
        for (int i = 0; i < insertModels.count(); i++)
        {
            if (insertModels.at(i).getType() == "AUDIO")
                typeId = std::find_if(typeModels.begin(), typeModels.end(), TypeModel::ByName("AUDIO"))->getId();
            else if (insertModels.at(i).getType() == "MOVIE")
                typeId = std::find_if(typeModels.begin(), typeModels.end(), TypeModel::ByName("MOVIE"))->getId();
            else if (insertModels.at(i).getType() == "STILL")
                typeId = std::find_if(typeModels.begin(), typeModels.end(), TypeModel::ByName("STILL"))->getId();

            QString query = QString("INSERT INTO Library (Name, DeviceId, TypeId, ThumbnailId, Timecode) VALUES('%1', %2, %3, %4, '%5')")
                                    .arg(insertModels.at(i).getName()).arg(deviceId).arg(typeId).arg(insertModels.at(i).getThumbnailId()).arg(insertModels.at(i).getTimecode());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateLibraryTemplate(const QString& address, const QList<LibraryModel>& deleteModels, const QList<LibraryModel>& insertModels)
{
    QMutexLocker locker(&mutex);

    int deviceId = getDeviceByAddress(address).getId();
    QList<TypeModel> typeModels = getType();
    int typeId = std::find_if(typeModels.begin(), typeModels.end(), TypeModel::ByName("TEMPLATE"))->getId();

    QSqlDatabase::database().transaction();

    QSqlQuery sql;
    if (deleteModels.count() > 0)
    {
        for (int i = 0; i < deleteModels.count(); i++)
        {
            QString query = QString("DELETE FROM Library WHERE Id = %1").arg(deleteModels.at(i).getId());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    if (insertModels.count() > 0)
    {
        for (int i = 0; i < insertModels.count(); i++)
        {
            QString query = QString("INSERT INTO Library (Name, DeviceId, TypeId, ThumbnailId, Timecode) VALUES('%1', %2, %3, %4, '%5')")
                                    .arg(insertModels.at(i).getName()).arg(deviceId).arg(typeId).arg(insertModels.at(i).getThumbnailId()).arg(insertModels.at(i).getTimecode());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    QSqlDatabase::database().commit();
}

void DatabaseManager::updateLibraryData(const QString& address, const QList<LibraryModel>& deleteModels, const QList<LibraryModel>& insertModels)
{
    QMutexLocker locker(&mutex);

    int deviceId = getDeviceByAddress(address).getId();
    QList<TypeModel> typeModels = getType();

    QSqlDatabase::database().transaction();

    QSqlQuery sql;
    if (deleteModels.count() > 0)
    {
        for (int i = 0; i < deleteModels.count(); i++)
        {
            QString query = QString("DELETE FROM Thumbnail WHERE Id = %1").arg(deleteModels.at(i).getThumbnailId());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

            query = QString("DELETE FROM Library WHERE Id = %1 AND TypeId = 2").arg(deleteModels.at(i).getId());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    if (insertModels.count() > 0)
    {
        int typeId;
        for (int i = 0; i < insertModels.count(); i++)
        {
            if (insertModels.at(i).getType() == "DATA")
                typeId = std::find_if(typeModels.begin(), typeModels.end(), TypeModel::ByName("DATA"))->getId();

            QString query = QString("INSERT INTO Library (Name, DeviceId, TypeId, ThumbnailId, Timecode) VALUES('%1', %2, %3, %4, '%5')")
                                    .arg(insertModels.at(i).getName()).arg(deviceId).arg(typeId).arg(insertModels.at(i).getThumbnailId()).arg(insertModels.at(i).getTimecode());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteLibrary(int deviceId)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM Library WHERE DeviceId = %1").arg(deviceId);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QList<ThumbnailModel> DatabaseManager::getThumbnailByDeviceAddress(const QString& address)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Data, t.Timestamp, t.Size, l.Name, d.Address FROM Thumbnail t, Library l, Device d "
                            "WHERE d.Address = '%1' AND l.DeviceId = d.Id AND l.ThumbnailId = t.Id").arg(address);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QList<ThumbnailModel> models;
    while (sql.next())
        models.push_back(ThumbnailModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                                        sql.value(3).toString(), sql.value(4).toString(), sql.value(5).toString()));

    return models;
}

ThumbnailModel DatabaseManager::getThumbnailByNameAndDeviceName(const QString& name, const QString& deviceName)
{
    QMutexLocker locker(&mutex);

    QString query = QString("SELECT t.Id, t.Data, t.Timestamp, t.Size, l.Name, d.Name, d.Address FROM Thumbnail t, Library l, Device d "
                            "WHERE l.Name = '%1' AND d.Name = '%2' AND l.ThumbnailId = t.Id").arg(name).arg(deviceName);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return ThumbnailModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString(),
                          sql.value(3).toString(), sql.value(4).toString(), sql.value(5).toString());
}

void DatabaseManager::updateThumbnail(const ThumbnailModel& model)
{
    QMutexLocker locker(&mutex);

    int deviceId = getDeviceByAddress(model.getAddress()).getId();
    const QList<LibraryModel>& libraryModels = getLibraryByNameAndDeviceId(model.getName(), deviceId);

    QSqlDatabase::database().transaction();

    QSqlQuery sql;
    if (libraryModels.count() > 0)
    {
        for (int i = 0; i < libraryModels.count(); i++)
        {
            const LibraryModel& libraryModel = libraryModels.at(i);
            if (libraryModel.getThumbnailId() > 0)
            {
                QString query = QString("UPDATE Thumbnail SET Data = '%1', Timestamp = '%2', Size = '%3' WHERE Id = %4")
                                        .arg(model.getData()).arg(model.getTimestamp()).arg(model.getSize()).arg(libraryModel.getThumbnailId());

                if (!sql.exec(query))
                   qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
            }
            else
            {
                QString query = QString("INSERT INTO Thumbnail (Data, Timestamp, Size) VALUES('%1', '%2', '%3')").arg(model.getData()).arg(model.getTimestamp()).arg(model.getSize());

                if (!sql.exec(query))
                   qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

                query = QString("UPDATE Library SET ThumbnailId = %1 WHERE Id = %2").arg(sql.lastInsertId().toInt()).arg(libraryModel.getId());

                if (!sql.exec(query))
                   qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
            }
        }
    }

    QSqlDatabase::database().commit();
}

void DatabaseManager::deleteThumbnails()
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM Thumbnail");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    const QList<LibraryModel>& models = this->getLibraryMedia();
    for (int i = 0; i < models.count(); i++)
    {
        const LibraryModel& model = models.at(i);
        if (model.getThumbnailId() > 0)
        {
            QString query = QString("UPDATE Library SET ThumbnailId = 0 WHERE Id = %1").arg(model.getId());

            if (!sql.exec(query))
               qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
        }
    }

    QSqlDatabase::database().commit();

    // Shrink file on disk.
    query = QString("VACUUM Thumbnail");
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());
}

/*
 * GetServerIp - returns primary or shadow servers ip
 * @shadow - if true returns primary server ip otherwise shadow servers ip
 */
QString DatabaseManager::GetServerIp(int shadow)
{
    QMutexLocker locker(&mutex);
    QString query;
    QSqlQuery sql;

    if (shadow) {
        query = "SELECT address FROM device where shadow=\"Yes\"";
        if (!sql.exec(query))
           qCritical() << QString("SQL Error: Failed to get Primary server ip.");
    } else {
        query = "SELECT address FROM device where shadow=\"No\"";
        if (!sql.exec(query))
           qCritical() << QString("SQL Error: Failed to get shadow server ip.");
    }
    sql.first();

    return sql.value(0).toString();
}

QString DatabaseManager::GetRazunaApiKey()
{
    QMutexLocker locker(&mutex);
    QString query;
    QSqlQuery sql;

    query = "SELECT apikey from Razuna";

    if (!sql.exec(query))
        qCritical() << QString("SQL Error: Failed To Extract Razuna API key");

    sql.first();

    return sql.value(0).toString();
}

/*
 *getDbUserName - returns Database username
 *@shadow - indicates whether it's for primary or shadow server
 */
QString DatabaseManager::getDbUserName(QString server)
{
    QMutexLocker locker(&mutex);
    QString query;
    QSqlQuery sql;

    query = QString("SELECT DbUserName FROM Device WHERE Address='%1'").arg(server);

    qDebug() << "getDbUserName query " << query;

    if (!sql.exec(query))
        qCritical() << QString("SQL Error: Get Database UserName");

    sql.first();

    return sql.value(0).toString();
}

QString DatabaseManager::getDbUserPass(QString server)
{
    QMutexLocker locker(&mutex);
    QString query;
    QSqlQuery sql;

    query = QString("SELECT DbUserPass FROM Device WHERE Address='%1'").arg(server);

    qDebug() << "getDbUserName query " << query;

    if (!sql.exec(query))
        qCritical() << QString("SQL Error: Get Database Password");

    sql.first();

    return sql.value(0).toString();
}

QList<RazunaModel> DatabaseManager::getRazuna()
{
    QMutexLocker locker(&mutex);
    QString query("SELECT Id, Name, apikey from Razuna");

    QSqlQuery sql;

    if (!sql.exec(query))
        qCritical() << QString("Failed to Get Razuna info");

    QList<RazunaModel> models;
    while(sql.next())
        models.push_back(RazunaModel(sql.value(0).toInt(), sql.value(1).toString(), sql.value(2).toString()));

    return models;
}

void DatabaseManager::insertRazuna(const RazunaModel& model)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO Razuna (Name, apikey) "
                            "VALUES('%1', '%2')").arg(model.getName()).arg(model.getApiKey());
    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::DeleteRazuna(int id)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE FROM Razuna WHERE Id = %1").arg(id);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

QString DatabaseManager::GetScrollerText()
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("SELECT news from TextScroller");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    sql.first();

    return sql.value(0).toString();
}

void DatabaseManager::ScrollerTextDel()
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("DELETE from TextScroller");

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::ScrollerTextUpdate(QString text)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("UPDATE TextScroller SET news = '%1'").arg(text);

    QSqlQuery sql;
    if (!sql.exec(query))
       qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}

void DatabaseManager::ScrollerTextInsert(QString text)
{
    QMutexLocker locker(&mutex);

    QSqlDatabase::database().transaction();

    QString query = QString("INSERT INTO TextScroller (news) VALUES('%1')").arg(text);

    QSqlQuery sql;
    if (!sql.exec(query))
        qCritical() << QString("Failed to execute: %1, Error: %2").arg(query).arg(sql.lastError().text());

    QSqlDatabase::database().commit();
}
