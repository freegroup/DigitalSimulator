<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">

	<!-- The main template. Processing starts here -->
	<xsl:template match="/circuit">
		<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:layout-master-set>
				<fo:simple-page-master master-name="simple" page-height="29.7cm" page-width="21cm" margin-top="1cm" margin-bottom="2cm" margin-left="2.5cm" margin-right="2.5cm">
					<fo:region-body margin-top="1cm"/>
					<fo:region-end extent="1cm"/>
					<fo:region-before extent="1cm"/>
					<fo:region-after extent="1cm"/>
				</fo:simple-page-master>
			</fo:layout-master-set>
			<fo:page-sequence master-reference="simple" initial-page-number="1">
				<!--
					print the header of the page
				-->
				<fo:static-content  flow-name="xsl-region-before">
					<fo:block  text-align="center" font-size="8pt" font-family="sans-serif" line-height="5pt">
						[ www.DigitalSimulator.de ]
					</fo:block>
				</fo:static-content>
				
				<!--
					print the footer of the page
				-->
				<fo:static-content background-color="black"  flow-name="xsl-region-after">
					<fo:block text-align="end" font-size="10pt" font-family="sans-serif" line-height="10pt">
						Seite <fo:page-number/>
					</fo:block>
				</fo:static-content>

				<!-- 
					print the content itself
				-->
				<fo:flow flow-name="xsl-region-body">
				<fo:block>
				        <fo:block font-size="20pt"   text-align="center" font-family="sans-serif"   space-after.optimum="5pt">
					     <xsl:text >Schaltungsbeschreibung</xsl:text><xsl:text disable-output-escaping="yes"> </xsl:text><xsl:value-of select="@name"/>

					</fo:block>
				        <fo:block font-size="15pt" font-family="sans-serif"   space-after.optimum="5pt">
					     <xsl:text >Bauteilliste</xsl:text>
					</fo:block>
					<xsl:for-each select="parts/part">
					    <fo:block font-size="10pt" font-family="sans-serif"   space-after.optimum="5pt">
						<xsl:value-of select="@partNumber"/><xsl:text disable-output-escaping="yes">) </xsl:text>
						<xsl:value-of select="@name"/><xsl:text disable-output-escaping="yes"> </xsl:text>
				      	    </fo:block>
					</xsl:for-each>
				        <fo:block font-size="15pt" font-family="sans-serif"   space-after.optimum="5pt" space-before.optimum="15pt">
					<xsl:text >Verbindungen (Kabelbrücken)</xsl:text>
					</fo:block>
					<xsl:for-each select="connections/connection">
					    <fo:block font-size="10pt" font-family="sans-serif"   space-after.optimum="5pt">
						<xsl:text disable-output-escaping="yes">Bauteil </xsl:text><xsl:value-of select="@fromPart"/><xsl:text disable-output-escaping="yes">) </xsl:text>
						<xsl:text disable-output-escaping="yes">Pin </xsl:text><xsl:value-of select="@fromPin"/><xsl:text disable-output-escaping="yes">) </xsl:text>
						<xsl:text disable-output-escaping="yes">verbinden mit Bauteil </xsl:text><xsl:value-of select="@toPart"/><xsl:text disable-output-escaping="yes">) </xsl:text>
						<xsl:text disable-output-escaping="yes">Pin </xsl:text><xsl:value-of select="@toPin"/><xsl:text disable-output-escaping="yes">) </xsl:text>
				      	    </fo:block>
					</xsl:for-each>
				  </fo:block>
				</fo:flow>
			</fo:page-sequence>
		</fo:root>
	</xsl:template>
</xsl:stylesheet>

