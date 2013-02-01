<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1311163593645" ID="ID_504385361" MODIFIED="1311338506068" TEXT="Leah">
<node CREATED="1311338490109" ID="ID_1134748856" MODIFIED="1311340291033" POSITION="left" TEXT="Control tasks">
<node CREATED="1311173517635" ID="ID_1498130012" MODIFIED="1311338468855" STYLE="fork" TEXT="Handle Bounds change in forms to resize also the window">
<icon BUILTIN="button_ok"/>
</node>
<node CREATED="1311163599445" FOLDED="true" ID="ID_1001316110" MODIFIED="1311338629379" TEXT="Transform the coordinates in paint event to coordinates relative to control">
<icon BUILTIN="button_ok"/>
<node CREATED="1311163622470" ID="ID_58762259" MODIFIED="1311338428734" TEXT="Allows double buffering to run without any other special handling">
<icon BUILTIN="button_ok"/>
</node>
<node CREATED="1311338572862" ID="ID_526061618" MODIFIED="1311338599453" TEXT="Rectangle in paint is cropped to parent control coordinates!">
<icon BUILTIN="messagebox_warning"/>
</node>
</node>
<node CREATED="1311173942739" FOLDED="true" ID="ID_1630200696" MODIFIED="1311338615260" TEXT="Implement window invalidate in controls">
<icon BUILTIN="button_ok"/>
<node CREATED="1311173964236" FOLDED="true" ID="ID_620350396" MODIFIED="1311338612220" TEXT="Set up in hierarchy to the form">
<icon BUILTIN="button_ok"/>
<node CREATED="1311198500251" ID="ID_1264346599" MODIFIED="1311338527409" TEXT="Retrieve the Window from the form">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node CREATED="1311173973349" FOLDED="true" ID="ID_209455422" MODIFIED="1311338613156" TEXT="Invalidate window in form">
<icon BUILTIN="closed"/>
<node CREATED="1311338536288" ID="ID_1927831784" MODIFIED="1311338545232" TEXT="Instead invalidate window in Control">
<icon BUILTIN="button_ok"/>
</node>
</node>
</node>
<node CREATED="1311339020317" FOLDED="true" ID="ID_1626097898" MODIFIED="1311339498490" TEXT="Send key events to children">
<icon BUILTIN="button_ok"/>
<node CREATED="1311339067106" ID="ID_65732495" MODIFIED="1311339136750" TEXT="Do we have a focused child?">
<node CREATED="1311339138774" ID="ID_387927944" MODIFIED="1311339145125" TEXT="Send the key event to the child"/>
</node>
<node CREATED="1311339147677" ID="ID_584081431" MODIFIED="1311339160301" TEXT="The event was handled?">
<node CREATED="1311339179131" ID="ID_606542110" MODIFIED="1311339188907" TEXT="Don&apos;t do anything more"/>
</node>
<node CREATED="1311339161181" ID="ID_47185992" MODIFIED="1311339176599" TEXT="Raise key event"/>
</node>
<node CREATED="1311339441892" FOLDED="true" ID="ID_1405416665" MODIFIED="1311340255414" TEXT="Bring to Front / Send to Back">
<icon BUILTIN="button_ok"/>
<node CREATED="1311339487921" ID="ID_1249805032" MODIFIED="1311339490134" TEXT="Bring to Front">
<node CREATED="1311339502249" ID="ID_231265180" MODIFIED="1311339522320" TEXT="Move control as last in the parent&apos;s queue"/>
</node>
<node CREATED="1311339490514" ID="ID_901433837" MODIFIED="1311339492291" TEXT="Send to Back">
<node CREATED="1311339525712" ID="ID_39500912" MODIFIED="1311339532952" TEXT="Move control as first in the parent&apos;s queue"/>
</node>
</node>
<node CREATED="1311339697150" FOLDED="true" ID="ID_1452490666" MODIFIED="1311339900418" TEXT="Handle control creation">
<node CREATED="1311339703678" ID="ID_784448416" MODIFIED="1311339717641" TEXT="Control should be created on Create event"/>
<node CREATED="1311339718325" ID="ID_1495001392" MODIFIED="1311339728189" TEXT="By overriding OnCreate event"/>
<node CREATED="1311339728580" ID="ID_1786109138" MODIFIED="1311339746124" TEXT="Create event is raised when the control is added to some parent"/>
<node CREATED="1311339757746" ID="ID_1161986515" MODIFIED="1311339760908" TEXT="Add a Created property">
<node CREATED="1311339764746" ID="ID_1195660701" MODIFIED="1311339781762" TEXT="Don&apos;t raise events, don&apos;t do much until the control is Created"/>
<node CREATED="1311339784073" ID="ID_1851167403" MODIFIED="1311339883265" TEXT="Construct some form of state machine when the control should start raising events">
<arrowlink DESTINATION="ID_719074076" ENDARROW="Default" ENDINCLINATION="1353;0;" ID="Arrow_ID_1639872883" STARTARROW="None" STARTINCLINATION="1353;0;"/>
</node>
</node>
</node>
<node CREATED="1311340299475" FOLDED="true" ID="ID_1891118682" MODIFIED="1311585039538" TEXT="Receive Focus">
<icon BUILTIN="button_ok"/>
<node CREATED="1311340320058" ID="ID_456488984" MODIFIED="1311340328630" TEXT="Ask parent to receive focus first"/>
<node CREATED="1311340411653" ID="ID_163430731" MODIFIED="1311347485100" TEXT="Ask parent to focus this">
<node CREATED="1311340329138" ID="ID_1136065004" MODIFIED="1311340409182" TEXT="Make focused sibling lose focus"/>
<node CREATED="1311340436707" ID="ID_1499990900" MODIFIED="1311347517128" TEXT="Set parent&apos;s FocusChild to this"/>
<node CREATED="1311347526017" ID="ID_266052212" MODIFIED="1311347529801" TEXT="Focus this"/>
</node>
</node>
<node CREATED="1311585028657" ID="ID_59077968" MODIFIED="1311585036959" TEXT="Mouse events handling"/>
</node>
<node CREATED="1311339809247" ID="ID_1070606251" MODIFIED="1311339814233" POSITION="right" TEXT="Properties">
<node CREATED="1311339816015" ID="ID_719074076" MODIFIED="1311339883265" TEXT="Add mechanics to disable property changed events"/>
</node>
<node CREATED="1311348201322" ID="ID_55944661" MODIFIED="1311585046356" POSITION="right" TEXT="Label control">
<icon BUILTIN="button_ok"/>
<node CREATED="1311348208610" ID="ID_1564831098" MODIFIED="1311348211355" TEXT="Implement label"/>
</node>
</node>
</map>
