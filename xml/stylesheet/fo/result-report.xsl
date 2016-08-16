<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:layout-master-set>
				<!-- Title Page Layout -->
				<fo:simple-page-master master-name="all-pages" page-height="29.7cm" page-width="21cm" font-family="sans-serif" margin-top="0.5cm" margin-bottom="1cm" margin-left="2cm" margin-right="2cm">
					<fo:region-body region-name="Body" margin-top="2cm" margin-bottom="2cm" />
					<fo:region-before region-name="Header" extent="2cm" />
					<fo:region-after region-name="Footer" extent="2cm" text-align="end" />
				</fo:simple-page-master>
				<fo:page-sequence-master master-name="default-sequence">
					<fo:repeatable-page-master-reference master-reference="all-pages"/>
				</fo:page-sequence-master>
			</fo:layout-master-set>
			<!-- Page Content -->
			<fo:page-sequence master-reference="default-sequence">
				<fo:static-content flow-name="Header" font-size="10pt">
					<fo:block>
						This is an example Header with usefull information...
					</fo:block>
				</fo:static-content>
				<fo:static-content flow-name="Footer" font-size="10pt">
					<fo:block>
						Page <fo:page-number/> of <fo:page-number-citation ref-id="terminator"/>
					</fo:block>
				</fo:static-content>
				<fo:flow flow-name="Body" font-size="12pt" text-align="justify" >
					<fo:block space-after="2cm">
						<fo:external-graphic src="stylesheet/images/dummy_logo.jpg" content-height="71px" vertical-align="middle"/>
					</fo:block>
					<fo:block>
						<fo:table border="0.5pt solid black" text-align="center">
							<fo:table-column column-width="8cm"/>
							<fo:table-column column-width="8cm"/>
							<fo:table-header background-color="#9acd32">
								<fo:table-row>
									<fo:table-cell padding="6pt" border="0.5pt solid black">
										<fo:block font-weight="bold">Bla</fo:block>
									</fo:table-cell>
									<fo:table-cell padding="6pt" border="0.5pt solid black">
										<fo:block font-weight="bold">Blubb</fo:block>
									</fo:table-cell>
								</fo:table-row>
							</fo:table-header>
							<fo:table-body>
								<xsl:apply-templates select="//Test" />
							</fo:table-body>
						</fo:table>
					</fo:block>
					<fo:block id="terminator"/>
				</fo:flow>
			</fo:page-sequence>
		</fo:root>
	</xsl:template> 
	<xsl:template match="//Test">
		<fo:table-row>
			<fo:table-cell padding="6pt" border="0.5pt solid black">
				<fo:block>
					<xsl:value-of select="@Name"/>
				</fo:block>
			</fo:table-cell>
			<fo:table-cell padding="6pt" border="0.5pt solid black">
				<fo:block>
        			<xsl:value-of select="Result/@Value"/>
				</fo:block>
			</fo:table-cell>
		</fo:table-row>
	</xsl:template>
</xsl:stylesheet>
