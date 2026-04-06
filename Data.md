
# XML Mapper Nested DataSets

The RAD Studio XML Mapper handles nested datasets by identifying repeating nodes within an XML document and mapping them to Nested DataSets (represented as  objects) in a data packet. This process allows a hierarchical XML structure to be transformed into a master-detail relationship within a single . [1, 2, 3]
Key Mechanisms

- Node Identification: The tool distinguishes between single-occurrence nodes and repeating nodes.

- Single nodes (e.g., ) or attributes (e.g., ) typically map to standard fields (ftString, ftInteger, etc.).
- Repeating nodes (nested element nodes) are identified as candidates for nested datasets.

- DataPacket Mapping: When creating a mapping, the XML Mapper generates a data packet structure where:

    - The Parent node maps to a record in the master dataset.
    - The Child nodes that repeat are represented as a field of type .

- Hierarchy Support: XML Mapper can handle deep nesting. A  can support up to 15 levels of nested data set fields, and each of those can contain another 15, enabling very complex data structures. [1, 3, 4, 5, 6]

## Working with Nested Data at Runtime
To use these mappings in your application:

1. Transformation File (.xtr): Use XML Mapper to define the relationship and save it as a transformation file.
2. TXMLTransform: Use the  component to apply the  file and convert the XML into a data packet.
3. TDataSetField: In your Delphi or C++Builder code, the nested data is accessed through a TDataSetField. You can link a separate  to this field via its  property to display or edit the detail records. [2, 7, 8, 9, 10]

### Advantages

• Master-Detail Efficiency: All related data (master and details) is packaged into a single unit, which is ideal for cached updates.
• Transactional Updates: When applying updates, the master and all nested records are processed in an "all or nothing" fashion within a single transaction. [3]

## AI responses may include mistakes.

https://docwiki.embarcadero.com/RADStudio/Athens/en/Mapping_Between_XML_Nodes_and_Data_Packet_Fields

https://docwiki.embarcadero.com/Libraries/Sydney/en/Data.DB.TDataSetField

https://www.youtube.com/watch?v=xARBcQ5dSjA

https://docwiki.embarcadero.com/RADStudio/Sydney/en/XML_Mapper

https://docwiki.embarcadero.com/RADStudio/Sydney/en/Using_XMLMapper

https://blogs.embarcadero.com/easily-learn-to-store-data-in-a-nested-dataset-using-firedac-with-firedac-tfdmemtable-nesteddataset-sample/

https://docwiki.embarcadero.com/RADStudio/Athens/en/Working_with_Dataset_Fields

https://learndelphi.org/everything-you-need-to-know-about-the-xml-mapper/

https://docwiki.embarcadero.com/RADStudio/Athens/en/Converting_XML_Documents_into_Data_Packets

https://docwiki.embarcadero.com/RADStudio/Athens/en/Using_XML_in_Database_Applications

