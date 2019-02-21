<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="angelo">
<packages>
<package name="ESP32" urn="urn:adsk.eagle:footprint:22390/1" locally_modified="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="19.05" y1="0.635" x2="19.685" y2="1.27" width="0.1524" layer="21"/>
<wire x1="19.685" y1="1.27" x2="20.955" y2="1.27" width="0.1524" layer="21"/>
<wire x1="20.955" y1="1.27" x2="21.59" y2="0.635" width="0.1524" layer="21"/>
<wire x1="21.59" y1="0.635" x2="21.59" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="21.59" y1="-0.635" x2="20.955" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="20.955" y1="-1.27" x2="19.685" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="19.685" y1="-1.27" x2="19.05" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="14.605" y1="1.27" x2="15.875" y2="1.27" width="0.1524" layer="21"/>
<wire x1="15.875" y1="1.27" x2="16.51" y2="0.635" width="0.1524" layer="21"/>
<wire x1="16.51" y1="0.635" x2="16.51" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="16.51" y1="-0.635" x2="15.875" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="16.51" y1="0.635" x2="17.145" y2="1.27" width="0.1524" layer="21"/>
<wire x1="17.145" y1="1.27" x2="18.415" y2="1.27" width="0.1524" layer="21"/>
<wire x1="18.415" y1="1.27" x2="19.05" y2="0.635" width="0.1524" layer="21"/>
<wire x1="19.05" y1="0.635" x2="19.05" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="18.415" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="18.415" y1="-1.27" x2="17.145" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="17.145" y1="-1.27" x2="16.51" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="11.43" y1="0.635" x2="12.065" y2="1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="1.27" x2="13.335" y2="1.27" width="0.1524" layer="21"/>
<wire x1="13.335" y1="1.27" x2="13.97" y2="0.635" width="0.1524" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="13.335" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="11.43" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="14.605" y1="1.27" x2="13.97" y2="0.635" width="0.1524" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="14.605" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="15.875" y1="-1.27" x2="14.605" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="0.635" x2="8.89" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.795" y2="1.27" width="0.1524" layer="21"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.1524" layer="21"/>
<wire x1="11.43" y1="0.635" x2="11.43" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="0.635" x2="6.35" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-6.35" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="0.635" x2="-6.35" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="-0.635" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="0.635" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-1.27" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.35" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="0.635" x2="-10.795" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="1.27" x2="-9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-8.89" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="0.635" x2="-8.89" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-0.635" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-1.27" x2="-10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-1.27" x2="-11.43" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-8.89" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="1.27" x2="-14.605" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="1.27" x2="-13.97" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="0.635" x2="-13.97" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="-0.635" x2="-14.605" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="0.635" x2="-13.335" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="1.27" x2="-12.065" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="1.27" x2="-11.43" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="0.635" x2="-11.43" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="-0.635" x2="-12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="-1.27" x2="-13.335" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="-1.27" x2="-13.97" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="0.635" x2="-18.415" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="1.27" x2="-17.145" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="1.27" x2="-16.51" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="0.635" x2="-16.51" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-0.635" x2="-17.145" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="-1.27" x2="-18.415" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="-1.27" x2="-19.05" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="1.27" x2="-16.51" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="-0.635" x2="-15.875" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="-1.27" x2="-15.875" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-23.495" y1="1.27" x2="-22.225" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="1.27" x2="-21.59" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="0.635" x2="-21.59" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="-0.635" x2="-22.225" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="0.635" x2="-20.955" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="1.27" x2="-19.685" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="1.27" x2="-19.05" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="0.635" x2="-19.05" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="-0.635" x2="-19.685" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-1.27" x2="-20.955" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="-1.27" x2="-21.59" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="0.635" x2="-24.13" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-23.495" y1="1.27" x2="-24.13" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="-0.635" x2="-23.495" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="-1.27" x2="-23.495" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="21.59" y1="0.635" x2="22.225" y2="1.27" width="0.1524" layer="21"/>
<wire x1="22.225" y1="1.27" x2="23.495" y2="1.27" width="0.1524" layer="21"/>
<wire x1="23.495" y1="1.27" x2="24.13" y2="0.635" width="0.1524" layer="21"/>
<wire x1="24.13" y1="0.635" x2="24.13" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="24.13" y1="-0.635" x2="23.495" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="23.495" y1="-1.27" x2="22.225" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="22.225" y1="-1.27" x2="21.59" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-22.86" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-20.32" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-17.78" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-15.24" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="-12.7" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="-10.16" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="-7.62" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="-5.08" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="9" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="10" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="11" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="12" x="5.08" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="13" x="7.62" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="14" x="10.16" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="15" x="12.7" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="16" x="15.24" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="17" x="17.78" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="18" x="20.32" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="19" x="22.86" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-24.2062" y="27.2288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-24.13" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="20.066" y1="-0.254" x2="20.574" y2="0.254" layer="51"/>
<rectangle x1="17.526" y1="-0.254" x2="18.034" y2="0.254" layer="51"/>
<rectangle x1="14.986" y1="-0.254" x2="15.494" y2="0.254" layer="51"/>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="-5.334" y1="-0.254" x2="-4.826" y2="0.254" layer="51"/>
<rectangle x1="-7.874" y1="-0.254" x2="-7.366" y2="0.254" layer="51"/>
<rectangle x1="-10.414" y1="-0.254" x2="-9.906" y2="0.254" layer="51"/>
<rectangle x1="-12.954" y1="-0.254" x2="-12.446" y2="0.254" layer="51"/>
<rectangle x1="-15.494" y1="-0.254" x2="-14.986" y2="0.254" layer="51"/>
<rectangle x1="-18.034" y1="-0.254" x2="-17.526" y2="0.254" layer="51"/>
<rectangle x1="-20.574" y1="-0.254" x2="-20.066" y2="0.254" layer="51"/>
<rectangle x1="-23.114" y1="-0.254" x2="-22.606" y2="0.254" layer="51"/>
<rectangle x1="22.606" y1="-0.254" x2="23.114" y2="0.254" layer="51"/>
<wire x1="19.05" y1="25.4" x2="19.685" y2="26.035" width="0.1524" layer="21"/>
<wire x1="19.685" y1="26.035" x2="20.955" y2="26.035" width="0.1524" layer="21"/>
<wire x1="20.955" y1="26.035" x2="21.59" y2="25.4" width="0.1524" layer="21"/>
<wire x1="21.59" y1="25.4" x2="21.59" y2="24.13" width="0.1524" layer="21"/>
<wire x1="21.59" y1="24.13" x2="20.955" y2="23.495" width="0.1524" layer="21"/>
<wire x1="20.955" y1="23.495" x2="19.685" y2="23.495" width="0.1524" layer="21"/>
<wire x1="19.685" y1="23.495" x2="19.05" y2="24.13" width="0.1524" layer="21"/>
<wire x1="14.605" y1="26.035" x2="15.875" y2="26.035" width="0.1524" layer="21"/>
<wire x1="15.875" y1="26.035" x2="16.51" y2="25.4" width="0.1524" layer="21"/>
<wire x1="16.51" y1="25.4" x2="16.51" y2="24.13" width="0.1524" layer="21"/>
<wire x1="16.51" y1="24.13" x2="15.875" y2="23.495" width="0.1524" layer="21"/>
<wire x1="16.51" y1="25.4" x2="17.145" y2="26.035" width="0.1524" layer="21"/>
<wire x1="17.145" y1="26.035" x2="18.415" y2="26.035" width="0.1524" layer="21"/>
<wire x1="18.415" y1="26.035" x2="19.05" y2="25.4" width="0.1524" layer="21"/>
<wire x1="19.05" y1="25.4" x2="19.05" y2="24.13" width="0.1524" layer="21"/>
<wire x1="19.05" y1="24.13" x2="18.415" y2="23.495" width="0.1524" layer="21"/>
<wire x1="18.415" y1="23.495" x2="17.145" y2="23.495" width="0.1524" layer="21"/>
<wire x1="17.145" y1="23.495" x2="16.51" y2="24.13" width="0.1524" layer="21"/>
<wire x1="11.43" y1="25.4" x2="12.065" y2="26.035" width="0.1524" layer="21"/>
<wire x1="12.065" y1="26.035" x2="13.335" y2="26.035" width="0.1524" layer="21"/>
<wire x1="13.335" y1="26.035" x2="13.97" y2="25.4" width="0.1524" layer="21"/>
<wire x1="13.97" y1="25.4" x2="13.97" y2="24.13" width="0.1524" layer="21"/>
<wire x1="13.97" y1="24.13" x2="13.335" y2="23.495" width="0.1524" layer="21"/>
<wire x1="13.335" y1="23.495" x2="12.065" y2="23.495" width="0.1524" layer="21"/>
<wire x1="12.065" y1="23.495" x2="11.43" y2="24.13" width="0.1524" layer="21"/>
<wire x1="14.605" y1="26.035" x2="13.97" y2="25.4" width="0.1524" layer="21"/>
<wire x1="13.97" y1="24.13" x2="14.605" y2="23.495" width="0.1524" layer="21"/>
<wire x1="15.875" y1="23.495" x2="14.605" y2="23.495" width="0.1524" layer="21"/>
<wire x1="6.985" y1="26.035" x2="8.255" y2="26.035" width="0.1524" layer="21"/>
<wire x1="8.255" y1="26.035" x2="8.89" y2="25.4" width="0.1524" layer="21"/>
<wire x1="8.89" y1="25.4" x2="8.89" y2="24.13" width="0.1524" layer="21"/>
<wire x1="8.89" y1="24.13" x2="8.255" y2="23.495" width="0.1524" layer="21"/>
<wire x1="8.89" y1="25.4" x2="9.525" y2="26.035" width="0.1524" layer="21"/>
<wire x1="9.525" y1="26.035" x2="10.795" y2="26.035" width="0.1524" layer="21"/>
<wire x1="10.795" y1="26.035" x2="11.43" y2="25.4" width="0.1524" layer="21"/>
<wire x1="11.43" y1="25.4" x2="11.43" y2="24.13" width="0.1524" layer="21"/>
<wire x1="11.43" y1="24.13" x2="10.795" y2="23.495" width="0.1524" layer="21"/>
<wire x1="10.795" y1="23.495" x2="9.525" y2="23.495" width="0.1524" layer="21"/>
<wire x1="9.525" y1="23.495" x2="8.89" y2="24.13" width="0.1524" layer="21"/>
<wire x1="3.81" y1="25.4" x2="4.445" y2="26.035" width="0.1524" layer="21"/>
<wire x1="4.445" y1="26.035" x2="5.715" y2="26.035" width="0.1524" layer="21"/>
<wire x1="5.715" y1="26.035" x2="6.35" y2="25.4" width="0.1524" layer="21"/>
<wire x1="6.35" y1="25.4" x2="6.35" y2="24.13" width="0.1524" layer="21"/>
<wire x1="6.35" y1="24.13" x2="5.715" y2="23.495" width="0.1524" layer="21"/>
<wire x1="5.715" y1="23.495" x2="4.445" y2="23.495" width="0.1524" layer="21"/>
<wire x1="4.445" y1="23.495" x2="3.81" y2="24.13" width="0.1524" layer="21"/>
<wire x1="6.985" y1="26.035" x2="6.35" y2="25.4" width="0.1524" layer="21"/>
<wire x1="6.35" y1="24.13" x2="6.985" y2="23.495" width="0.1524" layer="21"/>
<wire x1="8.255" y1="23.495" x2="6.985" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="26.035" x2="0.635" y2="26.035" width="0.1524" layer="21"/>
<wire x1="0.635" y1="26.035" x2="1.27" y2="25.4" width="0.1524" layer="21"/>
<wire x1="1.27" y1="25.4" x2="1.27" y2="24.13" width="0.1524" layer="21"/>
<wire x1="1.27" y1="24.13" x2="0.635" y2="23.495" width="0.1524" layer="21"/>
<wire x1="1.27" y1="25.4" x2="1.905" y2="26.035" width="0.1524" layer="21"/>
<wire x1="1.905" y1="26.035" x2="3.175" y2="26.035" width="0.1524" layer="21"/>
<wire x1="3.175" y1="26.035" x2="3.81" y2="25.4" width="0.1524" layer="21"/>
<wire x1="3.81" y1="25.4" x2="3.81" y2="24.13" width="0.1524" layer="21"/>
<wire x1="3.81" y1="24.13" x2="3.175" y2="23.495" width="0.1524" layer="21"/>
<wire x1="3.175" y1="23.495" x2="1.905" y2="23.495" width="0.1524" layer="21"/>
<wire x1="1.905" y1="23.495" x2="1.27" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="25.4" x2="-3.175" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="26.035" x2="-1.905" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="26.035" x2="-1.27" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="25.4" x2="-1.27" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="24.13" x2="-1.905" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="23.495" x2="-3.175" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="23.495" x2="-3.81" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="26.035" x2="-1.27" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="24.13" x2="-0.635" y2="23.495" width="0.1524" layer="21"/>
<wire x1="0.635" y1="23.495" x2="-0.635" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="26.035" x2="-6.985" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="26.035" x2="-6.35" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="25.4" x2="-6.35" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="24.13" x2="-6.985" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="25.4" x2="-5.715" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="26.035" x2="-4.445" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="26.035" x2="-3.81" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="25.4" x2="-3.81" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="24.13" x2="-4.445" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="23.495" x2="-5.715" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="23.495" x2="-6.35" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="25.4" x2="-10.795" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="26.035" x2="-9.525" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="26.035" x2="-8.89" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="25.4" x2="-8.89" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="24.13" x2="-9.525" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="23.495" x2="-10.795" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="23.495" x2="-11.43" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="26.035" x2="-8.89" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="24.13" x2="-8.255" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="23.495" x2="-8.255" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="26.035" x2="-14.605" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="26.035" x2="-13.97" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="25.4" x2="-13.97" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="24.13" x2="-14.605" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="25.4" x2="-13.335" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="26.035" x2="-12.065" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="26.035" x2="-11.43" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="25.4" x2="-11.43" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="24.13" x2="-12.065" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="23.495" x2="-13.335" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="23.495" x2="-13.97" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="25.4" x2="-18.415" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="26.035" x2="-17.145" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="26.035" x2="-16.51" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="25.4" x2="-16.51" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="24.13" x2="-17.145" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="23.495" x2="-18.415" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="23.495" x2="-19.05" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="26.035" x2="-16.51" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="24.13" x2="-15.875" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="23.495" x2="-15.875" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-23.495" y1="26.035" x2="-22.225" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="26.035" x2="-21.59" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="25.4" x2="-21.59" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="24.13" x2="-22.225" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="25.4" x2="-20.955" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="26.035" x2="-19.685" y2="26.035" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="26.035" x2="-19.05" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="25.4" x2="-19.05" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="24.13" x2="-19.685" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="23.495" x2="-20.955" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="23.495" x2="-21.59" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="25.4" x2="-24.13" y2="24.13" width="0.1524" layer="21"/>
<wire x1="-23.495" y1="26.035" x2="-24.13" y2="25.4" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="24.13" x2="-23.495" y2="23.495" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="23.495" x2="-23.495" y2="23.495" width="0.1524" layer="21"/>
<wire x1="21.59" y1="25.4" x2="22.225" y2="26.035" width="0.1524" layer="21"/>
<wire x1="22.225" y1="26.035" x2="23.495" y2="26.035" width="0.1524" layer="21"/>
<wire x1="23.495" y1="26.035" x2="24.13" y2="25.4" width="0.1524" layer="21"/>
<wire x1="24.13" y1="25.4" x2="24.13" y2="24.13" width="0.1524" layer="21"/>
<wire x1="24.13" y1="24.13" x2="23.495" y2="23.495" width="0.1524" layer="21"/>
<wire x1="23.495" y1="23.495" x2="22.225" y2="23.495" width="0.1524" layer="21"/>
<wire x1="22.225" y1="23.495" x2="21.59" y2="24.13" width="0.1524" layer="21"/>
<pad name="20" x="-22.86" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="21" x="-20.32" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="22" x="-17.78" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="23" x="-15.24" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="24" x="-12.7" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="25" x="-10.16" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="26" x="-7.62" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="27" x="-5.08" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="28" x="-2.54" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="29" x="0" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="30" x="2.54" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="31" x="5.08" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="32" x="7.62" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="33" x="10.16" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="34" x="12.7" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="35" x="15.24" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="36" x="17.78" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="37" x="20.32" y="24.765" drill="1.016" shape="long" rot="R90"/>
<pad name="38" x="22.86" y="24.765" drill="1.016" shape="long" rot="R90"/>
<rectangle x1="20.066" y1="24.511" x2="20.574" y2="25.019" layer="51"/>
<rectangle x1="17.526" y1="24.511" x2="18.034" y2="25.019" layer="51"/>
<rectangle x1="14.986" y1="24.511" x2="15.494" y2="25.019" layer="51"/>
<rectangle x1="12.446" y1="24.511" x2="12.954" y2="25.019" layer="51"/>
<rectangle x1="9.906" y1="24.511" x2="10.414" y2="25.019" layer="51"/>
<rectangle x1="7.366" y1="24.511" x2="7.874" y2="25.019" layer="51"/>
<rectangle x1="4.826" y1="24.511" x2="5.334" y2="25.019" layer="51"/>
<rectangle x1="2.286" y1="24.511" x2="2.794" y2="25.019" layer="51"/>
<rectangle x1="-0.254" y1="24.511" x2="0.254" y2="25.019" layer="51"/>
<rectangle x1="-2.794" y1="24.511" x2="-2.286" y2="25.019" layer="51"/>
<rectangle x1="-5.334" y1="24.511" x2="-4.826" y2="25.019" layer="51"/>
<rectangle x1="-7.874" y1="24.511" x2="-7.366" y2="25.019" layer="51"/>
<rectangle x1="-10.414" y1="24.511" x2="-9.906" y2="25.019" layer="51"/>
<rectangle x1="-12.954" y1="24.511" x2="-12.446" y2="25.019" layer="51"/>
<rectangle x1="-15.494" y1="24.511" x2="-14.986" y2="25.019" layer="51"/>
<rectangle x1="-18.034" y1="24.511" x2="-17.526" y2="25.019" layer="51"/>
<rectangle x1="-20.574" y1="24.511" x2="-20.066" y2="25.019" layer="51"/>
<rectangle x1="-23.114" y1="24.511" x2="-22.606" y2="25.019" layer="51"/>
<rectangle x1="22.606" y1="24.511" x2="23.114" y2="25.019" layer="51"/>
<wire x1="-27.305" y1="-1.27" x2="27.94" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-27.305" y1="-1.27" x2="-27.305" y2="26.035" width="0.127" layer="51"/>
<wire x1="-27.305" y1="26.035" x2="27.94" y2="26.035" width="0.127" layer="51"/>
<wire x1="-27.305" y1="8.89" x2="-20.955" y2="8.89" width="0.127" layer="21"/>
<wire x1="-20.955" y1="8.89" x2="-20.955" y2="16.51" width="0.127" layer="21"/>
<wire x1="-20.955" y1="16.51" x2="-27.305" y2="16.51" width="0.127" layer="21"/>
<wire x1="-27.305" y1="15.875" x2="-26.67" y2="15.875" width="0.127" layer="21"/>
<wire x1="-26.67" y1="15.875" x2="-26.67" y2="9.525" width="0.127" layer="21"/>
<wire x1="-26.67" y1="9.525" x2="-27.305" y2="9.525" width="0.127" layer="21"/>
<wire x1="27.94" y1="26.035" x2="27.94" y2="20.955" width="0.127" layer="21"/>
<wire x1="27.94" y1="20.955" x2="27.94" y2="3.81" width="0.127" layer="21"/>
<wire x1="27.94" y1="3.81" x2="27.94" y2="-1.27" width="0.127" layer="21"/>
<wire x1="27.94" y1="20.955" x2="2.54" y2="20.955" width="0.127" layer="21"/>
<wire x1="2.54" y1="20.955" x2="2.54" y2="3.81" width="0.127" layer="21"/>
<wire x1="2.54" y1="3.81" x2="27.94" y2="3.81" width="0.127" layer="21"/>
<wire x1="3.175" y1="20.32" x2="22.225" y2="20.32" width="0.127" layer="21"/>
<wire x1="22.225" y1="20.32" x2="22.225" y2="4.445" width="0.127" layer="21"/>
<wire x1="22.225" y1="4.445" x2="3.175" y2="4.445" width="0.127" layer="21"/>
<wire x1="3.175" y1="4.445" x2="3.175" y2="20.32" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="ESP-WROOM-32">
<pin name="3V3" x="-12.7" y="43.18" length="point" direction="pwr"/>
<pin name="EN" x="-12.7" y="38.1" length="point" direction="in"/>
<pin name="IO36" x="-12.7" y="33.02" length="point" direction="in"/>
<pin name="IO39" x="-12.7" y="27.94" length="point" direction="in"/>
<pin name="IO34" x="-12.7" y="22.86" length="point" direction="in"/>
<pin name="IO35" x="-12.7" y="17.78" length="point" direction="in"/>
<pin name="IO32" x="-12.7" y="12.7" length="point"/>
<pin name="IO33" x="-12.7" y="7.62" length="point"/>
<pin name="IO25" x="-12.7" y="2.54" length="point"/>
<pin name="IO26" x="-12.7" y="-2.54" length="point"/>
<pin name="IO27" x="-12.7" y="-7.62" length="point"/>
<pin name="IO14" x="-12.7" y="-12.7" length="point"/>
<pin name="IO12" x="-12.7" y="-17.78" length="point" direction="out"/>
<pin name="GND" x="-12.7" y="-22.86" length="point" direction="pwr"/>
<pin name="IO13" x="-12.7" y="-27.94" length="point"/>
<pin name="SD2" x="-12.7" y="-33.02" length="point" direction="nc"/>
<pin name="SD3" x="-12.7" y="-38.1" length="point" direction="nc"/>
<pin name="CMD" x="-12.7" y="-43.18" length="point" direction="nc"/>
<pin name="5V" x="-12.7" y="-48.26" length="point" direction="pwr"/>
<pin name="GND1" x="12.7" y="43.18" length="point" direction="pwr" rot="R180"/>
<pin name="IO23" x="12.7" y="38.1" length="point" rot="R180"/>
<pin name="IO22" x="12.7" y="33.02" length="point" rot="R180"/>
<pin name="TXD" x="12.7" y="27.94" length="point" direction="nc" rot="R180"/>
<pin name="RXD" x="12.7" y="22.86" length="point" direction="nc" rot="R180"/>
<pin name="IO21" x="12.7" y="17.78" length="point" rot="R180"/>
<pin name="GND2" x="12.7" y="12.7" length="point" direction="pwr" rot="R180"/>
<pin name="IO19" x="12.7" y="7.62" length="point" rot="R180"/>
<pin name="IO18" x="12.7" y="2.54" length="point" rot="R180"/>
<pin name="IO5" x="12.7" y="-2.54" length="point" direction="out" rot="R180"/>
<pin name="IO17" x="12.7" y="-7.62" length="point" rot="R180"/>
<pin name="IO16" x="12.7" y="-12.7" length="point" rot="R180"/>
<pin name="IO4" x="12.7" y="-17.78" length="point" direction="out" rot="R180"/>
<pin name="IO0" x="12.7" y="-22.86" length="point" direction="out" rot="R180"/>
<pin name="IO2" x="12.7" y="-27.94" length="point" direction="out" rot="R180"/>
<pin name="IO15" x="12.7" y="-33.02" length="point" direction="out" rot="R180"/>
<pin name="SD1" x="12.7" y="-38.1" length="point" direction="nc" rot="R180"/>
<pin name="SD0" x="12.7" y="-43.18" length="point" direction="nc" rot="R180"/>
<pin name="CLK" x="12.7" y="-48.26" length="point" direction="nc" rot="R180"/>
<wire x1="-12.7" y1="45.72" x2="12.7" y2="45.72" width="0.254" layer="94"/>
<wire x1="12.7" y1="45.72" x2="12.7" y2="-50.8" width="0.254" layer="94"/>
<wire x1="12.7" y1="-50.8" x2="-12.7" y2="-50.8" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-50.8" x2="-12.7" y2="45.72" width="0.254" layer="94"/>
<text x="-12.7" y="45.72" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="-53.34" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32-DEVKIT-C" prefix="U">
<gates>
<gate name="G$1" symbol="ESP-WROOM-32" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32">
<connects>
<connect gate="G$1" pin="3V3" pad="38"/>
<connect gate="G$1" pin="5V" pad="20"/>
<connect gate="G$1" pin="CLK" pad="1"/>
<connect gate="G$1" pin="CMD" pad="21"/>
<connect gate="G$1" pin="EN" pad="37"/>
<connect gate="G$1" pin="GND" pad="25"/>
<connect gate="G$1" pin="GND1" pad="19"/>
<connect gate="G$1" pin="GND2" pad="13"/>
<connect gate="G$1" pin="IO0" pad="6"/>
<connect gate="G$1" pin="IO12" pad="26"/>
<connect gate="G$1" pin="IO13" pad="24"/>
<connect gate="G$1" pin="IO14" pad="27"/>
<connect gate="G$1" pin="IO15" pad="4"/>
<connect gate="G$1" pin="IO16" pad="8"/>
<connect gate="G$1" pin="IO17" pad="9"/>
<connect gate="G$1" pin="IO18" pad="11"/>
<connect gate="G$1" pin="IO19" pad="12"/>
<connect gate="G$1" pin="IO2" pad="5"/>
<connect gate="G$1" pin="IO21" pad="14"/>
<connect gate="G$1" pin="IO22" pad="17"/>
<connect gate="G$1" pin="IO23" pad="18"/>
<connect gate="G$1" pin="IO25" pad="30"/>
<connect gate="G$1" pin="IO26" pad="29"/>
<connect gate="G$1" pin="IO27" pad="28"/>
<connect gate="G$1" pin="IO32" pad="32"/>
<connect gate="G$1" pin="IO33" pad="31"/>
<connect gate="G$1" pin="IO34" pad="34"/>
<connect gate="G$1" pin="IO35" pad="33"/>
<connect gate="G$1" pin="IO36" pad="36"/>
<connect gate="G$1" pin="IO39" pad="35"/>
<connect gate="G$1" pin="IO4" pad="7"/>
<connect gate="G$1" pin="IO5" pad="10"/>
<connect gate="G$1" pin="RXD" pad="15"/>
<connect gate="G$1" pin="SD0" pad="2"/>
<connect gate="G$1" pin="SD1" pad="3"/>
<connect gate="G$1" pin="SD2" pad="23"/>
<connect gate="G$1" pin="SD3" pad="22"/>
<connect gate="G$1" pin="TXD" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A4L-LOC" urn="urn:adsk.eagle:symbol:13874/1" library_version="1">
<wire x1="256.54" y1="3.81" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="256.54" y1="8.89" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="256.54" y1="13.97" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="256.54" y1="19.05" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="3.81" x2="161.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="24.13" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="215.265" y1="24.13" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="246.38" y1="3.81" x2="246.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="215.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="215.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<text x="217.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="217.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="230.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="216.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A4L-LOC" urn="urn:adsk.eagle:component:13926/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A4L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="angelo" deviceset="ESP32-DEVKIT-C" device=""/>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="A4L-LOC" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="G$1" x="-45.72" y="2.54" smashed="yes">
<attribute name="NAME" x="-58.42" y="48.26" size="1.778" layer="95"/>
<attribute name="VALUE" x="-58.42" y="-50.8" size="1.778" layer="96"/>
</instance>
<instance part="FRAME1" gate="G$1" x="-124.46" y="-83.82" smashed="yes">
<attribute name="DRAWING_NAME" x="92.71" y="-68.58" size="2.54" layer="94"/>
<attribute name="LAST_DATE_TIME" x="92.71" y="-73.66" size="2.286" layer="94"/>
<attribute name="SHEET" x="106.045" y="-78.74" size="2.54" layer="94"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="3V3" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="3V3"/>
<wire x1="-58.42" y1="45.72" x2="-71.12" y2="45.72" width="0.1524" layer="91"/>
<label x="-71.12" y="45.72" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="B_UP" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO36"/>
<wire x1="-58.42" y1="35.56" x2="-71.12" y2="35.56" width="0.1524" layer="91"/>
<label x="-71.12" y="35.56" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="B_DOWN" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO39"/>
<wire x1="-58.42" y1="30.48" x2="-71.12" y2="30.48" width="0.1524" layer="91"/>
<label x="-71.12" y="30.48" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="B_LEFT" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO34"/>
<wire x1="-58.42" y1="25.4" x2="-71.12" y2="25.4" width="0.1524" layer="91"/>
<label x="-71.12" y="25.4" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="B_RIGHT" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="IO35"/>
<wire x1="-58.42" y1="20.32" x2="-71.12" y2="20.32" width="0.1524" layer="91"/>
<label x="-71.12" y="20.32" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
