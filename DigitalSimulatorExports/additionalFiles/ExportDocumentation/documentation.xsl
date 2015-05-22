<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE stylesheet [
	<!ENTITY st0 "stroke:#000000;stroke-width:0.25;fill:none">
	<!ENTITY stt0 "fill:#000000;font-family:Arial;font-size:5">
]>
<?xmlspysamplexml D:\FreeGroup\DigitalSimulatorExports\castor\circuit.xml?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
	<!-- The main template. Processing starts here -->
	<xsl:template match="/circuit">
		<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:layout-master-set>
				<fo:simple-page-master master-name="simple" page-height="29.7cm" page-width="21cm" margin-top="1cm" margin-bottom="1cm" margin-left="2.5cm" margin-right="2.5cm">
					<fo:region-body margin-top="1cm"/>
					<fo:region-end extent="1cm"/>
					<fo:region-before extent="1cm"/>
					<fo:region-after extent="0.4cm"/>
				</fo:simple-page-master>
			</fo:layout-master-set>
			<fo:page-sequence master-reference="simple" initial-page-number="1">
				<!--
					print the header of the page
				-->
				<fo:static-content flow-name="xsl-region-before">
					<fo:block text-align="center" font-size="8pt" font-family="sans-serif" line-height="5pt">
						[ www.DigitalSimulator.de ]
					</fo:block>
				</fo:static-content>
				<!--
					print the footer of the page
				-->
				<fo:static-content background-color="black" flow-name="xsl-region-after">
					<fo:block text-align="end" font-size="8pt" font-family="sans-serif" line-height="10pt">
						Seite <fo:page-number/>
					</fo:block>
				</fo:static-content>
				<!-- 
					print the content itself
				-->
				<fo:flow flow-name="xsl-region-body">
					<fo:block>
						<fo:block background-color="#EEEEEE" font-size="18pt" text-align="center" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text disable-output-escaping="yes"> [</xsl:text><xsl:value-of select="@name"/><xsl:text>]</xsl:text>
						</fo:block>
						 <fo:block font-size="18pt" space-after.optimum="5pt"  space-before.optimum="25pt">
						 	<xsl:text>Schaltung</xsl:text>
						 </fo:block>
						<!-- first print the short description from the documentation part -->
						<fo:block>
							<xsl:value-of select="//shortDescription"/>
						</fo:block>
						<fo:block  text-align="center">
							<fo:external-graphic src="url('file:///{//imagePath}')"/>
						</fo:block>
						<fo:block>
							<xsl:value-of select="//longDescription"/>
						</fo:block>

						<!--
							 print the developer info 
						-->
						 <fo:block font-size="18pt" space-after.optimum="5pt"  space-before.optimum="25pt">
						 	<xsl:text>Autor</xsl:text>
						 </fo:block>
						<fo:block>
			               <fo:table  table-layout="fixed">
			                 <fo:table-column column-width="20mm"/>
			                 <fo:table-column column-width="140mm"/>
			                 <fo:table-body>
			                   <fo:table-row>
			                     <fo:table-cell >
			                        <fo:block><xsl:text>Name: </xsl:text></fo:block>
			                      </fo:table-cell>
			                     <fo:table-cell >
			                        <fo:block><xsl:value-of select="//firstName"/><xsl:text disable-output-escaping="yes"> </xsl:text><xsl:value-of select="//lastName"/></fo:block>
			                      </fo:table-cell>
			                   </fo:table-row>
			                   <fo:table-row>
			                     <fo:table-cell >
			                        <fo:block><xsl:text>Straße: </xsl:text></fo:block>
			                      </fo:table-cell>
			                     <fo:table-cell >
			                        <fo:block><xsl:value-of select="//street"/><xsl:text disable-output-escaping="yes"> </xsl:text><xsl:value-of select="//number"/></fo:block>
			                      </fo:table-cell>
			                   </fo:table-row>
			                   <fo:table-row>
			                     <fo:table-cell >
			                        <fo:block><xsl:text>Ort: </xsl:text></fo:block>
			                      </fo:table-cell>
			                     <fo:table-cell >
			                        <fo:block><xsl:value-of select="//zipCode"/><xsl:text disable-output-escaping="yes"> </xsl:text><xsl:value-of select="//city"/></fo:block>
			                      </fo:table-cell>
			                   </fo:table-row>
			                   <fo:table-row>
			                     <fo:table-cell >
			                        <fo:block><xsl:text>eMail: </xsl:text></fo:block>
			                      </fo:table-cell>
			                     <fo:table-cell >
			                        <fo:block><xsl:value-of select="//eMail"/></fo:block>
			                      </fo:table-cell>
			                   </fo:table-row>
			                 </fo:table-body>
			               </fo:table>
			                </fo:block>

			
			
					</fo:block>
				</fo:flow>
			</fo:page-sequence>
		</fo:root>
	</xsl:template>
</xsl:stylesheet>
