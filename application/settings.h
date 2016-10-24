#ifndef SETTINGS_H
#define SETTINGS_H

#include "./targetlevelmodel.h"
#include "./knownfieldmodel.h"

#include <c++utilities/conversion/types.h>

#include <tagparser/tagvalue.h>
#include <tagparser/tag.h>
#include <tagparser/mediafileinfo.h>

#include <qtutilities/settingsdialog/qtsettings.h>

#include <QString>
#include <QByteArray>

namespace Settings {

enum class ActionEnabled
{
    Ask,
    Yes,
    No
};

enum class AdoptFields
{
    Never,
    WithinDirectory,
    Always
};

enum class MultipleTagHandling
{
    SingleEditorPerTarget,
    SeparateEditors
};

struct AutoCompletition
{
    AutoCompletition();
    bool insertTitleFromFilename = false;
    bool trimWhitespaces = true;
    bool formatNames = false;
    bool fixUmlauts = false;
    KnownFieldModel fields;
};

struct Editor
{
    Editor();
    AdoptFields adoptFields = AdoptFields::Never;
    bool saveAndShowNextOnEnter = false;
    bool askBeforeDeleting = true;
    MultipleTagHandling multipleTagHandling = MultipleTagHandling::SingleEditorPerTarget;
    bool hideTagSelectionComboBox = false;
    bool forceFullParse = false;
#ifndef TAGEDITOR_NO_WEBVIEW
    bool noWebView = false;
#endif
    bool hideCoverButtons = false;
    AutoCompletition autoCompletition;
    KnownFieldModel fields;
    TargetLevelModel defaultTargets;
};

enum class UnsupportedFieldHandling
{
    Ignore,
    Discard
};

struct FileBrowser
{
    bool hideBackupFiles = true;
    bool readOnly = true;
};

struct Id3Processing
{
    Media::TagUsage v1Usage = Media::TagUsage::Always;
    Media::TagUsage v2Usage = Media::TagUsage::Always;
    byte v2Version = 3;
    bool keepVersionOfExistingId3v2Tag = true;
    bool mergeMultipleSuccessiveId3v2Tags = true;
};

struct FileLayout
{
    bool forceRewrite = true;
    Media::ElementPosition preferredTagPosition = Media::ElementPosition::BeforeData;
    bool forceTagPosition = true;
    Media::ElementPosition preferredIndexPosition = Media::ElementPosition::BeforeData;
    bool forceIndexPosition = true;
    std::size_t minPadding = 0;
    std::size_t maxPadding = 0;
    std::size_t preferredPadding = 0;
};

struct TagProcessing
{
    Media::TagTextEncoding preferredEncoding = Media::TagTextEncoding::Utf8;
    UnsupportedFieldHandling unsupportedFieldHandling = UnsupportedFieldHandling::Ignore;
    bool autoTagManagement = true;
    Id3Processing id3;
    FileLayout fileLayout;
};

struct MainWindow
{
    QByteArray geometry;
    QByteArray state;
    QString currentFileBrowserDirectory;
    bool layoutLocked = false;
};

struct DbQuery
{
    DbQuery();
    bool widgetShown = false;
    bool override = false;
    KnownFieldModel fields;
    QString musicBrainzUrl;
    QString coverArtArchiveUrl;
    QString lyricsWikiaUrl;
};

struct RenamingUtility
{
    int scriptSource = 0;
    QString externalScript;
    QString editorScript;
};

struct Settings
{
    Editor editor;
    FileBrowser fileBrowser;
    TagProcessing tagPocessing;
    MainWindow mainWindow;
    DbQuery dbQuery;
    RenamingUtility renamingUtility;
    Dialogs::QtSettings qt;
};

Settings &values();
void restore();
void save();

}

#endif // SETTINGS_H
