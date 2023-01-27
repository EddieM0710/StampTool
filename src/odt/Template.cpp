/**
 * @file odt/Template.cpp
 * @author Eddie Monroe ( )
 * @brief Template for the output ODT file
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

/**
 * 
 * @todo Complete Documentation
 * 
 * @todo integrate GIT
 * 
 * 
 **************************************************/


 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "odt/Template.h"

#include "Defs.h"

namespace ODT {

wxString StylesTemplate = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
\
<office:document-styles xmlns:css3t=\"http://www.w3.org/TR/css3-text/\"\
    xmlns:grddl=\"http://www.w3.org/2003/g/data-view#\"\
    xmlns:xhtml=\"http://www.w3.org/1999/xhtml\"\
    xmlns:dom=\"http://www.w3.org/2001/xml-events\"\
    xmlns:form=\"urn:oasis:names:tc:opendocument:xmlns:form:1.0\"\
    xmlns:field=\"urn:openoffice:names:experimental:ooo-ms-interop:xmlns:field:1.0\"\
    xmlns:loext=\"urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0\"\
    xmlns:script=\"urn:oasis:names:tc:opendocument:xmlns:script:1.0\"\
    xmlns:drawooo=\"http://openoffice.org/2010/draw\"\
    xmlns:calcext=\"urn:org:documentfoundation:names:experimental:calc:xmlns:calcext:1.0\"\
    xmlns:math=\"http://www.w3.org/1998/Math/MathML\"\
    xmlns:tableooo=\"http://openoffice.org/2009/table\"\
    xmlns:of=\"urn:oasis:names:tc:opendocument:xmlns:of:1.2\"\
    xmlns:oooc=\"http://openoffice.org/2004/calc\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:fo=\"urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0\"\
    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\
    xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\"\
    xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\"\
    xmlns:ooo=\"http://openoffice.org/2004/office\"\
    xmlns:chart=\"urn:oasis:names:tc:opendocument:xmlns:chart:1.0\"\
    xmlns:style=\"urn:oasis:names:tc:opendocument:xmlns:style:1.0\"\
    xmlns:text=\"urn:oasis:names:tc:opendocument:xmlns:text:1.0\"\
    xmlns:rpt=\"http://openoffice.org/2005/report\"\
    xmlns:draw=\"urn:oasis:names:tc:opendocument:xmlns:drawing:1.0\"\
    xmlns:officeooo=\"http://openoffice.org/2009/office\"\
    xmlns:dr3d=\"urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0\"\
    xmlns:ooow=\"http://openoffice.org/2004/writer\"\
    xmlns:svg=\"urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0\"\
    xmlns:table=\"urn:oasis:names:tc:opendocument:xmlns:table:1.0\"\
    xmlns:number=\"urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0\" office:version=\"1.3\">\
    <office:font-face-decls>\
        <style:font-face style:name=\"Arial\" svg:font-family=\"Arial\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"Arial Unicode MS\" svg:font-family=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"FreeSans\" svg:font-family=\"FreeSans\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"FreeSans1\" svg:font-family=\"FreeSans\" style:font-family-generic=\"system\" style:font-pitch=\"variable\"/>\
        <style:font-face style:name=\"Times New Roman\" svg:font-family=\"&apos;Times New Roman&apos;\" style:font-family-generic=\"roman\"/>\
    </office:font-face-decls>\
    <office:styles>\
        <style:default-style style:family=\"graphic\">\
            <style:graphic-properties svg:stroke-color=\"#3465a4\" draw:fill-color=\"#729fcf\" fo:wrap-option=\"no-wrap\" draw:shadow-offset-x=\"3mm\" draw:shadow-offset-y=\"3mm\" draw:start-line-spacing-horizontal=\"2.83mm\" draw:start-line-spacing-vertical=\"2.83mm\" draw:end-line-spacing-horizontal=\"2.83mm\" draw:end-line-spacing-vertical=\"2.83mm\" style:flow-with-text=\"false\"/>\
            <style:paragraph-properties style:text-autospace=\"ideograph-alpha\" style:line-break=\"strict\" style:writing-mode=\"lr-tb\" style:font-independent-line-spacing=\"false\">\
                <style:tab-stops/>\
            </style:paragraph-properties>\
            <style:text-properties style:use-window-font-color=\"true\" loext:opacity=\"0%\" style:font-name=\"Times New Roman\" fo:font-size=\"12pt\" fo:language=\"en\" fo:country=\"US\" style:letter-kerning=\"true\" style:font-name-asian=\"Arial Unicode MS\" style:font-size-asian=\"10.5pt\" style:language-asian=\"zh\" style:country-asian=\"CN\" style:font-name-complex=\"FreeSans1\" style:font-size-complex=\"12pt\" style:language-complex=\"hi\" style:country-complex=\"IN\"/>\
        </style:default-style>\
        <style:default-style style:family=\"paragraph\">\
            <style:paragraph-properties fo:orphans=\"2\" fo:widows=\"2\" fo:hyphenation-ladder-count=\"no-limit\" style:text-autospace=\"ideograph-alpha\" style:punctuation-wrap=\"hanging\" style:line-break=\"strict\" style:tab-stop-distance=\"7.41mm\" style:writing-mode=\"page\"/>\
            <style:text-properties style:use-window-font-color=\"true\" loext:opacity=\"0%\" style:font-name=\"Times New Roman\" fo:font-size=\"12pt\" fo:language=\"en\" fo:country=\"US\" style:letter-kerning=\"true\" style:font-name-asian=\"Arial Unicode MS\" style:font-size-asian=\"10.5pt\" style:language-asian=\"zh\" style:country-asian=\"CN\" style:font-name-complex=\"FreeSans1\" style:font-size-complex=\"12pt\" style:language-complex=\"hi\" style:country-complex=\"IN\" fo:hyphenate=\"false\" fo:hyphenation-remain-char-count=\"2\" fo:hyphenation-push-char-count=\"2\" loext:hyphenation-no-caps=\"false\"/>\
        </style:default-style>\
        <style:default-style style:family=\"table\">\
            <style:table-properties table:border-model=\"collapsing\"/>\
        </style:default-style>\
        <style:default-style style:family=\"table-row\">\
            <style:table-row-properties fo:keep-together=\"auto\"/>\
        </style:default-style>\
        <style:style style:name=\"Standard\" style:family=\"paragraph\" style:class=\"text\"/>\
        <style:style style:name=\"Heading\" style:family=\"paragraph\" style:parent-style-name=\"Standard\" style:next-style-name=\"Text_20_body\" style:class=\"text\">\
            <style:paragraph-properties fo:margin-top=\"4.23mm\" fo:margin-bottom=\"2.12mm\" style:contextual-spacing=\"false\" fo:keep-with-next=\"always\"/>\
            <style:text-properties style:font-name=\"Arial\" fo:font-family=\"Arial\" style:font-family-generic=\"swiss\" fo:font-size=\"14pt\" style:font-name-asian=\"Arial Unicode MS\" style:font-family-asian=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic-asian=\"swiss\" style:font-size-asian=\"14pt\" style:font-name-complex=\"FreeSans1\" style:font-family-complex=\"FreeSans\" style:font-family-generic-complex=\"system\" style:font-pitch-complex=\"variable\" style:font-size-complex=\"14pt\"/>\
        </style:style>\
        <style:style style:name=\"Text_20_body\" style:display-name=\"Text body\" style:family=\"paragraph\" style:parent-style-name=\"Standard\" style:class=\"text\">\
            <style:paragraph-properties fo:margin-top=\"0mm\" fo:margin-bottom=\"2.47mm\" style:contextual-spacing=\"false\" fo:line-height=\"115%\"/>\
        </style:style>\
        <style:style style:name=\"List\" style:family=\"paragraph\" style:parent-style-name=\"Text_20_body\" style:class=\"list\">\
            <style:text-properties style:font-name=\"Times New Roman\" fo:font-family=\"&apos;Times New Roman&apos;\" style:font-family-generic=\"roman\" style:font-name-asian=\"Arial Unicode MS\" style:font-family-asian=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic-asian=\"swiss\" style:font-size-asian=\"12pt\" style:font-name-complex=\"FreeSans\" style:font-family-complex=\"FreeSans\" style:font-family-generic-complex=\"swiss\"/>\
        </style:style>\
        <style:style style:name=\"Caption\" style:family=\"paragraph\" style:parent-style-name=\"Standard\" style:class=\"extra\">\
            <style:paragraph-properties fo:margin-top=\"2.12mm\" fo:margin-bottom=\"2.12mm\" style:contextual-spacing=\"false\" text:number-lines=\"false\" text:line-number=\"0\"/>\
            <style:text-properties style:font-name=\"Times New Roman\" fo:font-family=\"&apos;Times New Roman&apos;\" style:font-family-generic=\"roman\" fo:font-size=\"12pt\" fo:font-style=\"italic\" style:font-name-asian=\"Arial Unicode MS\" style:font-family-asian=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic-asian=\"swiss\" style:font-size-asian=\"12pt\" style:font-style-asian=\"italic\" style:font-name-complex=\"FreeSans\" style:font-family-complex=\"FreeSans\" style:font-family-generic-complex=\"swiss\" style:font-size-complex=\"12pt\" style:font-style-complex=\"italic\"/>\
        </style:style>\
        <style:style style:name=\"Index\" style:family=\"paragraph\" style:parent-style-name=\"Standard\" style:class=\"index\">\
            <style:paragraph-properties text:number-lines=\"false\" text:line-number=\"0\"/>\
            <style:text-properties style:font-name=\"Times New Roman\" fo:font-family=\"&apos;Times New Roman&apos;\" style:font-family-generic=\"roman\" fo:language=\"zxx\" fo:country=\"none\" style:font-name-asian=\"Arial Unicode MS\" style:font-family-asian=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic-asian=\"swiss\" style:font-size-asian=\"12pt\" style:language-asian=\"zxx\" style:country-asian=\"none\" style:font-name-complex=\"FreeSans\" style:font-family-complex=\"FreeSans\" style:font-family-generic-complex=\"swiss\" style:language-complex=\"zxx\" style:country-complex=\"none\"/>\
        </style:style>\
        <text:outline-style style:name=\"Outline\">\
            <text:outline-level-style text:level=\"1\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"2\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"3\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"4\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"5\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"6\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"7\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"8\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"9\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
            <text:outline-level-style text:level=\"10\" style:num-format=\"\">\
                <style:list-level-properties text:list-level-position-and-space-mode=\"label-alignment\">\
                    <style:list-level-label-alignment text:label-followed-by=\"listtab\"/>\
                </style:list-level-properties>\
            </text:outline-level-style>\
        </text:outline-style>\
        <text:notes-configuration text:note-class=\"footnote\" style:num-format=\"1\" text:start-value=\"0\" text:footnotes-position=\"page\" text:start-numbering-at=\"document\"/>\
        <text:notes-configuration text:note-class=\"endnote\" style:num-format=\"i\" text:start-value=\"0\"/>\
        <text:linenumbering-configuration text:number-lines=\"false\" text:offset=\"4.99mm\" style:num-format=\"1\" text:number-position=\"left\" text:increment=\"5\"/>\
    </office:styles>\
    <office:automatic-styles>\
        <style:page-layout style:name=\"Mpm1\">\
            <style:page-layout-properties fo:page-width=\"215.9mm\" fo:page-height=\"279.4mm\" style:num-format=\"1\" style:print-orientation=\"portrait\" fo:margin-top=\"0mm\" fo:margin-bottom=\"0mm\" fo:margin-left=\"0mm\" fo:margin-right=\"0mm\" style:writing-mode=\"lr-tb\" style:footnote-max-height=\"0mm\" loext:margin-gutter=\"0mm\">\
                <style:footnote-sep style:width=\"0.18mm\" style:distance-before-sep=\"1.01mm\" style:distance-after-sep=\"1.01mm\" style:line-style=\"solid\" style:adjustment=\"left\" style:rel-width=\"25%\" style:color=\"#000000\"/>\
            </style:page-layout-properties>\
            <style:header-style/>\
            <style:footer-style/>\
        </style:page-layout>\
        <style:style style:name=\"Mdp1\" style:family=\"drawing-page\">\
            <style:drawing-page-properties draw:background-size=\"full\"/>\
        </style:style>\
    </office:automatic-styles>\
    <office:master-styles>\
        <style:master-page style:name=\"Standard\" style:page-layout-name=\"Mpm1\" draw:style-name=\"Mdp1\"/>\
    </office:master-styles>\
</office:document-styles>"};

wxString SettingsTemplate = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
\
<office:document-settings xmlns:config=\"urn:oasis:names:tc:opendocument:xmlns:config:1.0\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\"\
    xmlns:ooo=\"http://openoffice.org/2004/office\" office:version=\"1.3\">\
    <office:settings>\
        <config:config-item-set config:name=\"ooo:view-settings\">\
            <config:config-item config:name=\"ViewAreaTop\" config:type=\"long\">0</config:config-item>\
            <config:config-item config:name=\"ViewAreaLeft\" config:type=\"long\">0</config:config-item>\
            <config:config-item config:name=\"ViewAreaWidth\" config:type=\"long\">44148</config:config-item>\
            <config:config-item config:name=\"ViewAreaHeight\" config:type=\"long\">25718</config:config-item>\
            <config:config-item config:name=\"ShowRedlineChanges\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"InBrowseMode\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item-map-indexed config:name=\"Views\">\
                <config:config-item-map-entry>\
                    <config:config-item config:name=\"ViewId\" config:type=\"string\">view2</config:config-item>\
                    <config:config-item config:name=\"ViewLeft\" config:type=\"long\">11278</config:config-item>\
                    <config:config-item config:name=\"ViewTop\" config:type=\"long\">501</config:config-item>\
                    <config:config-item config:name=\"VisibleLeft\" config:type=\"long\">0</config:config-item>\
                    <config:config-item config:name=\"VisibleTop\" config:type=\"long\">0</config:config-item>\
                    <config:config-item config:name=\"VisibleRight\" config:type=\"long\">44147</config:config-item>\
                    <config:config-item config:name=\"VisibleBottom\" config:type=\"long\">25716</config:config-item>\
                    <config:config-item config:name=\"ZoomType\" config:type=\"short\">0</config:config-item>\
                    <config:config-item config:name=\"ViewLayoutColumns\" config:type=\"short\">0</config:config-item>\
                    <config:config-item config:name=\"ViewLayoutBookMode\" config:type=\"boolean\">false</config:config-item>\
                    <config:config-item config:name=\"ZoomFactor\" config:type=\"short\">89</config:config-item>\
                    <config:config-item config:name=\"IsSelectedFrame\" config:type=\"boolean\">false</config:config-item>\
                    <config:config-item config:name=\"KeepRatio\" config:type=\"boolean\">false</config:config-item>\
                    <config:config-item config:name=\"AnchoredTextOverflowLegacy\" config:type=\"boolean\">false</config:config-item>\
                </config:config-item-map-entry>\
            </config:config-item-map-indexed>\
        </config:config-item-set>\
        <config:config-item-set config:name=\"ooo:configuration-settings\">\
            <config:config-item config:name=\"PrintPaperFromSetup\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintFaxName\" config:type=\"string\"/>\
            <config:config-item config:name=\"PrintSingleJobs\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintProspectRTL\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintProspect\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintTextPlaceholder\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintTables\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrintPageBackground\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrintLeftPages\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrintAnnotationMode\" config:type=\"short\">0</config:config-item>\
            <config:config-item config:name=\"PrintControls\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrintHiddenText\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintDrawings\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"FootnoteInColumnToPageEnd\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"FrameAutowidthWithMorePara\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"HeaderSpacingBelowLastPara\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ProtectFields\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintReversed\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ProtectBookmarks\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmptyDbFieldHidesPara\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"UseOldPrinterMetrics\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"UseOldNumbering\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"AddExternalLeading\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"TreatSingleColumnBreakAsPageBreak\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"IsLabelDocument\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"RsidRoot\" config:type=\"int\">361456</config:config-item>\
            <config:config-item config:name=\"TabOverSpacing\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ConsiderTextWrapOnObjPos\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"TableRowKeep\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"TabsRelativeToIndent\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"AddParaLineSpacingToTableCells\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"AllowPrintJobCancel\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"GutterAtTop\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"UpdateFromTemplate\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"SaveVersionOnClose\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"UseFormerTextWrapping\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ChartAutoUpdate\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"ContinuousEndnotes\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"AddParaTableSpacingAtStart\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"AddParaTableSpacing\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"AddParaSpacingToTableCells\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"UseFormerLineSpacing\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"OutlineLevelYieldsNumbering\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"AlignTabStopPosition\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"DoNotJustifyLinesWithManualBreak\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmbedOnlyUsedFonts\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"LinkUpdateMode\" config:type=\"short\">1</config:config-item>\
            <config:config-item config:name=\"CurrentDatabaseCommandType\" config:type=\"int\">0</config:config-item>\
            <config:config-item config:name=\"CurrentDatabaseCommand\" config:type=\"string\"/>\
            <config:config-item config:name=\"CharacterCompressionType\" config:type=\"short\">0</config:config-item>\
            <config:config-item config:name=\"SmallCapsPercentage66\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ApplyUserData\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"StylesNoDefault\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmbeddedDatabaseName\" config:type=\"string\"/>\
            <config:config-item config:name=\"FloattableNomargins\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"BackgroundParaOverDrawings\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrinterName\" config:type=\"string\"/>\
            <config:config-item config:name=\"UseFormerObjectPositioning\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrinterSetup\" config:type=\"base64Binary\"/>\
            <config:config-item config:name=\"IgnoreFirstLineIndentInNumbering\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"CollapseEmptyCellPara\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"TabOverMargin\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"SaveGlobalDocumentLinks\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"CurrentDatabaseDataSource\" config:type=\"string\"/>\
            <config:config-item config:name=\"IsKernAsianPunctuation\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintEmptyPages\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"ProtectForm\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"AddVerticalFrameOffsets\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"SaveThumbnail\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrinterIndependentLayout\" config:type=\"string\">high-resolution</config:config-item>\
            <config:config-item config:name=\"PrinterPaperFromSetup\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"TabOverflow\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PrintGraphics\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"PropLineSpacingShrinksFirstLine\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"DoNotResetParaAttrsForNumFont\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"FieldAutoUpdate\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"IgnoreTabsAndBlanksForLineCalculation\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"RedlineProtectionKey\" config:type=\"base64Binary\"/>\
            <config:config-item config:name=\"EmbedComplexScriptFonts\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"LoadReadonly\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"DoNotCaptureDrawObjsOnPage\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ClipAsCharacterAnchoredWriterFlyFrames\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintBlackFonts\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"DisableOffPagePositioning\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"SurroundTextWrapSmall\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"UnxForceZeroExtLeading\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmbedAsianScriptFonts\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"TabAtLeftIndentForParagraphsInList\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"PrintRightPages\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"Rsid\" config:type=\"int\">361456</config:config-item>\
            <config:config-item config:name=\"MathBaselineAlignment\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"MsWordCompTrailingBlanks\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"MsWordCompMinLineHeightByFly\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"InvertBorderSpacing\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmbedFonts\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"UnbreakableNumberings\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"AddFrameOffsets\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ClippedPictures\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"EmbedLatinScriptFonts\" config:type=\"boolean\">true</config:config-item>\
            <config:config-item config:name=\"EmbedSystemFonts\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"ApplyParagraphMarkFormatToNumbering\" config:type=\"boolean\">false</config:config-item>\
            <config:config-item config:name=\"SubtractFlysAnchoredAtFlys\" config:type=\"boolean\">false</config:config-item>\
        </config:config-item-set>\
    </office:settings>\
</office:document-settings>"};

wxString ManifestTemplate = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<manifest:manifest xmlns:manifest=\"urn:oasis:names:tc:opendocument:xmlns:manifest:1.0\" manifest:version=\"1.3\" xmlns:loext=\"urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0\">\
 <manifest:file-entry manifest:full-path=\"/\" manifest:version=\"1.3\" manifest:media-type=\"application/vnd.oasis.opendocument.text\"/>\
 <manifest:file-entry manifest:full-path=\"styles.xml\" manifest:media-type=\"text/xml\"/>\
 <manifest:file-entry manifest:full-path=\"Configurations2/\" manifest:media-type=\"application/vnd.sun.xml.ui.configuration\"/>\
 <manifest:file-entry manifest:full-path=\"Thumbnails/thumbnail.png\" manifest:media-type=\"image/png\"/>\
 <manifest:file-entry manifest:full-path=\"content.xml\" manifest:media-type=\"text/xml\"/>\
 <manifest:file-entry manifest:full-path=\"meta.xml\" manifest:media-type=\"text/xml\"/>\
 <manifest:file-entry manifest:full-path=\"manifest.rdf\" manifest:media-type=\"application/rdf+xml\"/>\
 <manifest:file-entry manifest:full-path=\"settings.xml\" manifest:media-type=\"text/xml\"/>\
</manifest:manifest>"};

wxString ManifestRDFTemplate = {"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\
  <rdf:Description rdf:about=\"styles.xml\">\
    <rdf:type rdf:resource=\"http://docs.oasis-open.org/ns/office/1.2/meta/odf#StylesFile\"/>\
  </rdf:Description>\
  <rdf:Description rdf:about=\"\">\
    <ns0:hasPart xmlns:ns0=\"http://docs.oasis-open.org/ns/office/1.2/meta/pkg#\" rdf:resource=\"styles.xml\"/>\
  </rdf:Description>\
  <rdf:Description rdf:about=\"content.xml\">\
    <rdf:type rdf:resource=\"http://docs.oasis-open.org/ns/office/1.2/meta/odf#ContentFile\"/>\
  </rdf:Description>\
  <rdf:Description rdf:about=\"\">\
    <ns0:hasPart xmlns:ns0=\"http://docs.oasis-open.org/ns/office/1.2/meta/pkg#\" rdf:resource=\"content.xml\"/>\
  </rdf:Description>\
  <rdf:Description rdf:about=\"\">\
    <rdf:type rdf:resource=\"http://docs.oasis-open.org/ns/office/1.2/meta/pkg#Document\"/>\
  </rdf:Description>\
</rdf:RDF>"};

wxString MetaTemplate("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
\
<office:document-meta xmlns:grddl=\"http://www.w3.org/2003/g/data-view#\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\
    xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\"\
    xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\"\
    xmlns:ooo=\"http://openoffice.org/2004/office\" office:version=\"1.3\">\
    <office:meta>\
        <meta:creation-date>2023-01-13T19:35:09.408648306</meta:creation-date>\
        <dc:date>2023-01-13T19:36:53.253959499</dc:date>\
        <meta:editing-duration>PT1M44S</meta:editing-duration>\
        <meta:editing-cycles>1</meta:editing-cycles>\
        <meta:document-statistic meta:table-count=\"0\" meta:image-count=\"0\" meta:object-count=\"0\" meta:page-count=\"1\" meta:paragraph-count=\"0\" meta:word-count=\"0\" meta:character-count=\"0\" meta:non-whitespace-character-count=\"0\"/>\
        <meta:tool>LibreOffice/7.3.4.2$Linux_X86_64 LibreOffice_project/30$Build-2</meta:tool>\
    </office:meta>\
</office:document-meta>");



wxString ContentTemplate("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
\
<office:document-content xmlns:css3t=\"http://www.w3.org/TR/css3-text/\"\
    xmlns:grddl=\"http://www.w3.org/2003/g/data-view#\"\
    xmlns:xhtml=\"http://www.w3.org/1999/xhtml\"\
    xmlns:formx=\"urn:openoffice:names:experimental:ooxml-odf-interop:xmlns:form:1.0\"\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
    xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
    xmlns:dom=\"http://www.w3.org/2001/xml-events\"\
    xmlns:form=\"urn:oasis:names:tc:opendocument:xmlns:form:1.0\"\
    xmlns:xforms=\"http://www.w3.org/2002/xforms\"\
    xmlns:field=\"urn:openoffice:names:experimental:ooo-ms-interop:xmlns:field:1.0\"\
    xmlns:loext=\"urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0\"\
    xmlns:script=\"urn:oasis:names:tc:opendocument:xmlns:script:1.0\"\
    xmlns:drawooo=\"http://openoffice.org/2010/draw\"\
    xmlns:calcext=\"urn:org:documentfoundation:names:experimental:calc:xmlns:calcext:1.0\"\
    xmlns:math=\"http://www.w3.org/1998/Math/MathML\"\
    xmlns:tableooo=\"http://openoffice.org/2009/table\"\
    xmlns:of=\"urn:oasis:names:tc:opendocument:xmlns:of:1.2\"\
    xmlns:oooc=\"http://openoffice.org/2004/calc\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:fo=\"urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0\"\
    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\
    xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\"\
    xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\"\
    xmlns:ooo=\"http://openoffice.org/2004/office\"\
    xmlns:chart=\"urn:oasis:names:tc:opendocument:xmlns:chart:1.0\"\
    xmlns:style=\"urn:oasis:names:tc:opendocument:xmlns:style:1.0\"\
    xmlns:text=\"urn:oasis:names:tc:opendocument:xmlns:text:1.0\"\
    xmlns:rpt=\"http://openoffice.org/2005/report\"\
    xmlns:draw=\"urn:oasis:names:tc:opendocument:xmlns:drawing:1.0\"\
    xmlns:officeooo=\"http://openoffice.org/2009/office\"\
    xmlns:dr3d=\"urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0\"\
    xmlns:ooow=\"http://openoffice.org/2004/writer\"\
    xmlns:svg=\"urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0\"\
    xmlns:table=\"urn:oasis:names:tc:opendocument:xmlns:table:1.0\"\
    xmlns:number=\"urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0\" office:version=\"1.3\">\
    <office:scripts/>\
    <office:font-face-decls>\
        <style:font-face style:name=\"Arial\" svg:font-family=\"Arial\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"Arial Unicode MS\" svg:font-family=\"&apos;Arial Unicode MS&apos;\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"FreeSans\" svg:font-family=\"FreeSans\" style:font-family-generic=\"swiss\"/>\
        <style:font-face style:name=\"FreeSans1\" svg:font-family=\"FreeSans\" style:font-family-generic=\"system\" style:font-pitch=\"variable\"/>\
        <style:font-face style:name=\"Times New Roman\" svg:font-family=\"&apos;Times New Roman&apos;\" style:font-family-generic=\"roman\"/>\
    </office:font-face-decls>\
    <office:automatic-styles/>\
    <office:body>\
        <office:text>\
            <text:sequence-decls>\
                <text:sequence-decl text:display-outline-level=\"0\" text:name=\"Illustration\"/>\
                <text:sequence-decl text:display-outline-level=\"0\" text:name=\"Table\"/>\
                <text:sequence-decl text:display-outline-level=\"0\" text:name=\"Text\"/>\
                <text:sequence-decl text:display-outline-level=\"0\" text:name=\"Drawing\"/>\
                <text:sequence-decl text:display-outline-level=\"0\" text:name=\"Figure\"/>\
            </text:sequence-decls>\
            <text:p text:style-name=\"Standard\"/>\
        </office:text>\
    </office:body>\
</office:document-content>");

}