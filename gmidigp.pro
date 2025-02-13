QT -= gui
QT -= core

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gmchannelroute.cpp \
        gmchannelrouter.cpp \
        gmchannelrouterconfigurator.cpp \
        gp5outputstream.cpp \
        gtpoutputstream.cpp \
        main.cpp \
        midievent.cpp \
        midisequence.cpp \
        midisongreader.cpp \
        miditrack.cpp \
        songadjuster.cpp \
        temps.cpp \
        tgbeat.cpp \
        tgchannel.cpp \
        tgchannelparameter.cpp \
        tgchord.cpp \
        tgdivisiontype.cpp \
        tgduration.cpp \
        tgeffects.cpp \
        tgfactory.cpp \
        tglayout.cpp \
        tglyric.cpp \
        tgmarker.cpp \
        tgmeasure.cpp \
        tgmeasurebuffer.cpp \
        tgmeasureheader.cpp \
        tgnote.cpp \
        tgnoteeffect.cpp \
        tgnoteimpl.cpp \
        tgsong.cpp \
        tgsongmanager.cpp \
        tgstring.cpp \
        tgstroke.cpp \
        tgtempo.cpp \
        tgtext.cpp \
        tgtimesignature.cpp \
        tgtrack.cpp \
        tgvoice.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    tux/ControllerEventListener.java \
    tux/ControllerEventstd::vectorener.java \
    tux/GP1InputStream.java \
    tux/GP1InputStreamPlugin.java \
    tux/GP2InputStream.java \
    tux/GP2InputStreamPlugin.java \
    tux/GP3InputStream.java \
    tux/GP3InputStreamPlugin.java \
    tux/GP3OutputStream.java \
    tux/GP3OutputStreamPlugin.java \
    tux/GP4InputStream.java \
    tux/GP4InputStreamPlugin.java \
    tux/GP4OutputStream.java \
    tux/GP4OutputStreamPlugin.java \
    tux/GP5InputStream.java \
    tux/GP5InputStreamPlugin.java \
    tux/GP5OutputStream.java \
    tux/GP5OutputStreamPlugin.java \
    tux/GTPFileFormat.java \
    tux/GTPFileFormatDetector.java \
    tux/GTPFileFormatVersion.java \
    tux/GTPFormatException.java \
    tux/GTPInputStream.java \
    tux/GTPInputStreamPlugin.java \
    tux/GTPOutputStream.java \
    tux/GTPOutputStreamPlugin.java \
    tux/GTPPlugin.java \
    tux/GTPSettings.java \
    tux/GTPSettingsManager.java \
    tux/GTPVoiceJoiner.java \
    tux/Instrument.java \
    tux/InvalidMidiDataException.java \
    tux/MetaEventListener.java \
    tux/MetaEventstd::vectorener.java \
    tux/MetaMessage.java \
    tux/MidiChannel.java \
    tux/MidiDevice.java \
    tux/MidiDeviceReceiver.java \
    tux/MidiDeviceTransmitter.java \
    tux/MidiEvent.java \
    tux/MidiFileException.java \
    tux/MidiFileFormat.java \
    tux/MidiFileHeader.java \
    tux/MidiFileReader.java \
    tux/MidiFileWriter.java \
    tux/MidiMessage.java \
    tux/MidiMessageUtils.java \
    tux/MidiPlugin.java \
    tux/MidiSequence.java \
    tux/MidiSequenceHandlerImpl.java \
    tux/MidiSettings.java \
    tux/MidiSongReader.java \
    tux/MidiSongReaderPlugin.java \
    tux/MidiSongWriter.java \
    tux/MidiSongWriterPlugin.java \
    tux/MidiSystem.java \
    tux/MidiTrack.java \
    tux/MidiUnavailableException.java \
    tux/Patch.java \
    tux/Receiver.java \
    tux/ShortMessage.java \
    tux/Soundbank.java \
    tux/SoundbankResource.java \
    tux/Synthesizer.java \
    tux/SysexMessage.java \
    tux/TESongReader.java \
    tux/TGBeat.java \
    tux/TGBeatGroup.java \
    tux/TGBeatImpl.java \
    tux/TGBeatSpacing.java \
    tux/TGChannel.java \
    tux/TGChannelNames.java \
    tux/TGChannelParameter.java \
    tux/TGChord.java \
    tux/TGChordImpl.java \
    tux/TGColor.java \
    tux/TGController.java \
    tux/TGDivisionType.java \
    tux/TGDrumMap.java \
    tux/TGDuration.java \
    tux/TGEffectBend.java \
    tux/TGEffectGrace.java \
    tux/TGEffectHarmonic.java \
    tux/TGEffectTremoloBar.java \
    tux/TGEffectTremoloPicking.java \
    tux/TGEffectTrill.java \
    tux/TGFactoryImpl.java \
    tux/TGFileFormat.java \
    tux/TGFileFormatAvailabilityEvent.java \
    tux/TGFileFormatDetector.java \
    tux/TGFileFormatException.java \
    tux/TGFileFormatManager.java \
    tux/TGFileFormatUtils.java \
    tux/TGLayout.java \
    tux/TGLayoutHorizontal.java \
    tux/TGLayoutStyles.java \
    tux/TGLayoutVertical.java \
    tux/TGLyric.java \
    tux/TGLyricImpl.java \
    tux/TGMarker.java \
    tux/TGMeasure.java \
    tux/TGMeasureBuffer.java \
    tux/TGMeasureHeader.java \
    tux/TGMeasureHeaderImpl.java \
    tux/TGMeasureImpl.java \
    tux/TGMeasureManager.java \
    tux/TGNotation.java \
    tux/TGNote.java \
    tux/TGNoteEffect.java \
    tux/TGNoteImpl.java \
    tux/TGResourceBuffer.java \
    tux/TGResources.java \
    tux/TGScale.java \
    tux/TGSong.java \
    tux/TGSongExporter.java \
    tux/TGSongImporter.java \
    tux/TGSongManager.java \
    tux/TGSongPersistenceHandle.java \
    tux/TGSongPersistenceHandler.java \
    tux/TGSongPersistenceHelper.java \
    tux/TGSongReader.java \
    tux/TGSongReaderHandle.java \
    tux/TGSongReaderHelper.java \
    tux/TGSongStream.java \
    tux/TGSongStreamContext.java \
    tux/TGSongStreamProvider.java \
    tux/TGSongWriter.java \
    tux/TGSongWriterHandle.java \
    tux/TGSongWriterHelper.java \
    tux/TGSpacing.java \
    tux/TGString.java \
    tux/TGStroke.java \
    tux/TGTempo.java \
    tux/TGText.java \
    tux/TGTextImpl.java \
    tux/TGTimeSignature.java \
    tux/TGTrack.java \
    tux/TGTrackImpl.java \
    tux/TGTrackManager.java \
    tux/TGTrackSpacing.java \
    tux/TGVelocities.java \
    tux/TGVoice.java \
    tux/TGVoiceImpl.java \
    tux/Transmitter.java \
    tux/VoiceStatus.java

HEADERS += \
    gmchannelroute.h \
    gmchannelrouter.h \
    gmchannelrouterconfigurator.h \
    gp5outputstream.h \
    gtpoutputstream.h \
    midievent.h \
    midisequence.h \
    midisongreader.h \
    miditrack.h \
    songadjuster.h \
    temps.h \
    tgbeat.h \
    tgchannel.h \
    tgchannelparameter.h \
    tgchord.h \
    tgdivisiontype.h \
    tgduration.h \
    tgeffects.h \
    tgfactory.h \
    tglayout.h \
    tglyric.h \
    tgmarker.h \
    tgmeasure.h \
    tgmeasurebuffer.h \
    tgmeasureheader.h \
    tgmeasureimpl.cpp \
    tgmeasureimpl.h \
    tgnote.h \
    tgnoteeffect.h \
    tgnoteimpl.h \
    tgsong.h \
    tgsongmanager.h \
    tgstring.h \
    tgstroke.h \
    tgtempo.h \
    tgtext.h \
    tgtimesignature.h \
    tgtrack.h \
    tgvoice.h
