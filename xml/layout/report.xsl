<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" indent="yes" doctype-system="about:legacy-compat"/>
  <xsl:template match="/report">
<!-- HTML HEADER -->
<html>
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" media="screen" type="text/css" href="layout/browser.css"/>
        <link rel="stylesheet" media="print" type="text/css" href="layout/browser.css"/>
    </head>
<!-- HTML HEADER -->
    <body>
        <table class="header">
            <tr>
                <td>
		    <p>Patient: <xsl:value-of select="patient/name"/><xsl:text> </xsl:text><xsl:value-of select="patient/surname"/>, geb. <xsl:value-of select="patient/dob"/></p>
		    <p>Befundaufnahme: <xsl:value-of select="date"/></p>
                    <h1> <xsl:value-of select="type"/> </h1>
                    <p>Therapeut: <xsl:value-of select="therapist/name"/><xsl:text> </xsl:text><xsl:value-of select="therapist/surname"/></p>
                </td>
            </tr>
        </table>
            <xsl:if test="function">
            <!-- FUNCTION TABLE HEADER-->
            <table class="tbl">
                <tr>
                    <th rowspan="2" colspan="2" class="left">KÖRPERFUNKTIONEN</th>
                    <th colspan="6" >Schädigung</th>
                </tr>
                <tr>
                    <th></th>
                    <th>0</th>
                    <th>1</th>
                    <th>2</th>
                    <th>3</th>
                    <th>4</th>
                </tr>
                <xsl:for-each select="function">
                <!-- FUNCTION TABLE ROW-->
                <tr>
                    <td width="7%"><xsl:value-of select="id"/></td>
                    <td width="63%" class="left"><xsl:value-of select="description"/></td>
                    <td width="10%"></td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td colspan="8" class="left"><i><xsl:value-of select="freetext"/></i></td>
                </tr>
                </xsl:for-each>
            </table>
            </xsl:if>
            <xsl:if test="structure">
            <!-- STRUCTURE TABLE HEADER-->
            <table class="tbl">
                <tr>
                    <th rowspan="2" colspan="2" class="left">KÖRPERSTRUKTUREN</th>
                    <th colspan="6" >Schädigung</th>
                </tr>
                <tr>
                    <th></th>
                    <th>0</th>
                    <th>1</th>
                    <th>2</th>
                    <th>3</th>
                    <th>4</th>
                </tr>
                <xsl:for-each select="structure">
                <!-- STRUCTURE TABLE ROW-->
                <tr>
                    <td width="7%"><xsl:value-of select="id"/></td>
                    <td width="63%" class="left"><xsl:value-of select="description"/></td>
                    <td width="10%"></td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td colspan="8" class="left"><i><xsl:value-of select="freetext"/></i></td>
                </tr>
                </xsl:for-each>
            </table>
            </xsl:if>
            <xsl:if test="partizipation">
            <!-- PARTICIPATION TABLE HEADER-->
            <table class="tbl">
                <tr>
                    <th rowspan="2" colspan="2" class="left">AKTIVITÄTEN UND PARTIZIPATION [TEILHABE]</th>
                    <th colspan="6" >Beeinträchtigung</th>
                </tr>
                <tr>
                    <th></th>
                    <th>0</th>
                    <th>1</th>
                    <th>2</th>
                    <th>3</th>
                    <th>4</th>
                </tr>
                <xsl:for-each select="partizipation">
                <!-- PARTICIPATION TABLE ROW-->
                <tr>
                    <td width="7%" rowspan="2"><xsl:value-of select="id"/></td>
                    <td width="63%" rowspan="2" class="left"><xsl:value-of select="description"/></td>
                    <td width="10%" class="part">L</td>
                    <td class="part"><xsl:if test="value = 0">X</xsl:if></td>
                    <td class="part"><xsl:if test="value = 1">X</xsl:if></td>
                    <td class="part"><xsl:if test="value = 2">X</xsl:if></td>
                    <td class="part"><xsl:if test="value = 3">X</xsl:if></td>
                    <td class="part"><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td width="10%" class="part">LF</td>
                    <td class="part"></td>
                    <td class="part"></td>
                    <td class="part"></td>
                    <td class="part"></td>
                    <td class="part"></td>
                </tr>
                <tr>
                    <td colspan="8" class="left"><i><xsl:value-of select="freetext"/></i></td>
                </tr>
                </xsl:for-each>
            </table>
            </xsl:if>
            <xsl:if test="context">
            <!-- CONTEXT TABLE HEADER-->
            <table class="tbl">
                <tr>
                    <th rowspan="2" colspan="2" class="left">UMWELTFAKTOREN</th>
                    <th colspan="4" >Förderfaktor</th>
                    <th colspan="5" >Barriere</th>
                </tr>
                <tr>
                    <th>+4</th>
                    <th>+3</th>
                    <th>+2</th>
                    <th>+1</th>
                    <th>0</th>
                    <th>1</th>
                    <th>2</th>
                    <th>3</th>
                    <th>4</th>
                </tr>
                <xsl:for-each select="context">
                <!-- CONTEXT TABLE ROW-->
                <tr>
                    <td width="7%" ><xsl:value-of select="id"/></td>
                    <td width="63%" class="left"><xsl:value-of select="description"/></td>
                    <td><xsl:if test="value = 8">X</xsl:if></td>
                    <td><xsl:if test="value = 7">X</xsl:if></td>
                    <td><xsl:if test="value = 6">X</xsl:if></td>
                    <td><xsl:if test="value = 5">X</xsl:if></td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td colspan="11" class="left"><i><xsl:value-of select="freetext"/></i></td>
                </tr>
                </xsl:for-each>
            </table>
            </xsl:if>
            <!--Description-->
            <p class="desc">In den Körperfunktionen, Körperstrukturen, Aktivitäten und Partizipation: 0 = kein Problem, 1 = leichtes Problem, 2 = mäßiges Problem, 3 = erhebliches Problem, 4 = vollständiges Problem; In den Umweltfaktoren: 0 = keine Barriere/Förderfaktor, 1 = leichte Barriere, 2 = mäßige Barriere, 3 = erhebliche Barriere, 4 = vollständige Barriere, +1 = leichter Förderfaktor, +2 = mäßiger Förderfaktor, +3 = erheblicher Förderfaktor, +4 = vollständiger Förderfaktor<br />8 = nicht spezifiziert, 9 = nicht anwendbar<br />L = Leistung, LF = Leistungsfähigkeit
            </p>
            <!-- FREE TEXT -->
            <p><u>Erläuterung:</u><xsl:text> </xsl:text>
                                <xsl:call-template name="insertBreaks">
                                    <xsl:with-param name="pText" select="freetext"/>
                                </xsl:call-template>
            </p>
        <!-- FOOTER -->
        <p class="sig"><xsl:value-of select="therapist/office"/></p>
  </body>
</html>
  </xsl:template>
  
   <xsl:template match="text()" name="insertBreaks">
   <xsl:param name="pText" select="."/>

   <xsl:choose>
     <xsl:when test="not(contains($pText, '&#xA;'))">
       <xsl:copy-of select="$pText"/>
     </xsl:when>
     <xsl:otherwise>
       <xsl:value-of select="substring-before($pText, '&#xA;')"/>
       <br />
       <xsl:call-template name="insertBreaks">
         <xsl:with-param name="pText" select="substring-after($pText, '&#xA;')"/>
       </xsl:call-template>
     </xsl:otherwise>
   </xsl:choose>
 </xsl:template>
</xsl:stylesheet>
