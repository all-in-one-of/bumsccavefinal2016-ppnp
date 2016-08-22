# import the stuff we need to access houdini and parse xml
import hou
import xml.etree.ElementTree as et

# let us parse the xml
filepath = hou.getenv("XML") + '/sample_Thu Aug 18 09:40:16 2016.xml'
xmldata = et.parse(filepath)
skeleton = xmldata.getroot()

# let us init imp houdini variables to play around with the node network
node = hou.pwd()
root = hou.node('/obj')

# now we start

# first things first - create our geo object that will be the parent of everything
skeleton_node = root.createNode('geo')
skeleton_node.setName(skeleton.attrib['name'])

# delete the default nodes
for child in skeleton_node.children():
    child.destroy()

# edit the parameter interface of the skeleton node
# parmTemplate = hou.FloatParmTemplate("ths", "Thickness at Start", 1, default_value=([0]), min=0, max=10, min_is_strict=False)
# skeleton_node.addSpareParmTuple(parmTemplate, in_folder([Tapering]), create_missing_folders=True)
parm_group = node.parmTemplateGroup()
parm_folder = hou.FolderParmTemplate("folder", "Thickness and Tapering")
parm_folder.addParmTemplate(hou.FloatParmTemplate("ths", "Thickness Start", 1, default_value=([0.3])))
parm_folder.addParmTemplate(hou.FloatParmTemplate("thf", "Thickness Finish", 1, default_value=([0.3])))
parm_folder.addParmTemplate(hou.FloatParmTemplate("beta", "Tapering Factor", 1, default_value=([1])))
parm_group.append(parm_folder)
skeleton_node.setParmTemplateGroup(parm_group)

# for every path we must create a curve node
for path in skeleton:
    
    curve = skeleton_node.createNode('curve')
    curve.setName(path.attrib['name'])
    curve.parm('type').set(1)
    
    # empty list of vertices
    vertices = []
    for vertex in path:
        x = vertex.find('x')
        
        y = vertex.find('y')
        z = vertex.find('z')
        coord = x.text + ',' + y.text + ',' + z.text
        vertices.append(coord)
    
    coords = ' '.join(vertices)
    curve.parm('coords').set(coords)

sopcategory = hou.nodeTypeCategories()["Sop"]
curvetype = hou.nodeType(sopcategory, "curve")

i = 0
sweep_expr = str("ch('../ths')*(1-pow($"+"PT/$"+"NPT, ch('../beta'))) + ch('../thf')*pow($"+"PT/$"+"NPT, ch('../beta'))")
circle = skeleton_node.createNode('circle')
circle.parm('type').set(1)
for child in skeleton_node.children():
    if child.type() == curvetype:       
        sweep = skeleton_node.createNode('sweep')
        sweep.setInput(0, circle)
        sweep.setInput(1, child)
        sweep.parm('skin').set(1)
        sweep.parm('xformbyattribs').set(False)        
        sweep.parm('scale').setExpression(sweep_expr)
    i = i + 1
    
# merge all nodes together 
merge = skeleton_node.createNode('merge')

sweeptype = hou.nodeType(sopcategory, "sweep")
i = 0
for child in skeleton_node.children():
    if child.type() == sweeptype:
        merge.setInput(i, child)
    i = i + 1

merge.setDisplayFlag(1)



    
    
    


