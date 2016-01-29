<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" indent="yes" doctype-system="about:legacy-compat"/>
  <xsl:template match="/report">
<!-- HTML HEADER -->
<html>
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" media="screen" type="text/css" href="browser.css"/>
        <link rel="stylesheet" media="print" type="text/css" href="browser.css"/>
    </head>
<!-- HTML HEADER -->
    <body>
        <table class="header">
            <tr>
                <td>
                    <p align="right">Befundaufnahme: <xsl:value-of select="date"/></p>
		    <p>Patient: <xsl:value-of select="patient/name"/><xsl:text> </xsl:text><xsl:value-of select="patient/surname"/>, Geb.-Datum: <xsl:value-of select="patient/dob"/><br />Diagnose: <xsl:value-of select="patient/diagnosis"/></p>
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
                    <th colspan="6" class="left">Schädigung</th>
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
                    <td width="7%" rowspan="2"><xsl:value-of select="id"/></td>
                    <td width="63%" rowspan="2" class="left"><xsl:value-of select="description"/></td>
                    <td>LF</td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td>L</td>
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
                    <th colspan="6" class="left">Schädigung</th>
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
                    <td width="7%" rowspan="2"><xsl:value-of select="id"/></td>
                    <td width="63%" rowspan="2" class="left"><xsl:value-of select="description"/></td>
                    <td>LF</td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td>L</td>
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
            <xsl:if test="context">
            <!-- CONTEXT TABLE HEADER-->
            <table class="tbl">
                <tr>
                    <th rowspan="2" colspan="2" class="left">KONTEXTFAKTOREN</th>
                    <th colspan="6" class="left">Schädigung</th>
                </tr>
                <tr>
                    <th></th>
                    <th>0</th>
                    <th>1</th>
                    <th>2</th>
                    <th>3</th>
                    <th>4</th>
                </tr>
                <xsl:for-each select="context">
                <!-- CONTEXT TABLE ROW-->
                <tr>
                    <td width="7%" rowspan="2"><xsl:value-of select="id"/></td>
                    <td width="63%" rowspan="2" class="left"><xsl:value-of select="description"/></td>
                    <td>LF</td>
                    <td><xsl:if test="value = 0">X</xsl:if></td>
                    <td><xsl:if test="value = 1">X</xsl:if></td>
                    <td><xsl:if test="value = 2">X</xsl:if></td>
                    <td><xsl:if test="value = 3">X</xsl:if></td>
                    <td><xsl:if test="value = 4">X</xsl:if></td>
                </tr>
                <tr>
                    <td>L</td>
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
            <!-- FREE TEXT -->
            <p>Erläuterung: <xsl:value-of select="freetext"/></p>
        <!-- FOOTER -->
        <p class="sig"><xsl:value-of select="therapist/office"/></p>
  </body>
</html>
  </xsl:template>
</xsl:stylesheet>
