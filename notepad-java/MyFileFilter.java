//package p1;
import java.io.File;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;

/***************************************************/
class FileFilterDemo extends JFrame
{
JLabel myLabel;
JButton myButton;

JFileChooser chooser;

FileFilterDemo()
{
super("File Filter Demo");
myLabel=new JLabel("No file is choosed yet");
myButton=new JButton("Choose file");

ActionListener listener=
	new ActionListener()
{
public void actionPerformed(ActionEvent ev)
{
if (FileFilterDemo.this.chooser==null)
	chooser=new JFileChooser();
chooser.addChoosableFileFilter(new MyFileFilter(".java","Java Source Files(*.java)"));
chooser.addChoosableFileFilter(new MyFileFilter(".txt","Text Files(*.txt)"));
//filter=new MyFilter();	then filter is equivalent to select all files
if(chooser.showDialog(FileFilterDemo.this,"Select this")==JFileChooser.APPROVE_OPTION)
	FileFilterDemo.this.myLabel.setText(chooser.getSelectedFile().getPath());
}
};

myButton.addActionListener(listener);

add(myLabel,"Center");
add(myButton,"South");

setSize(300,300);
setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
}

public static void main(String[] args)
{
FileFilterDemo ffd=new FileFilterDemo();
ffd.setVisible(true);
}
}
/***************************************************/
public class MyFileFilter extends FileFilter
{
private String extension;
private String description;
////////////////
public MyFileFilter()
{
setExtension(null);
setDescription(null);
}
////////////////
public MyFileFilter(final String ext, final String desc)
{
setExtension(ext);
setDescription(desc);
}
////////////////
public boolean accept(File f)
{
final String filename=f.getName();

if(	f.isDirectory() || 
	extension==null || 
	filename.toUpperCase()
	.endsWith(extension.toUpperCase()))
	return true;
return false;

}
////////////////
public String getDescription()
{
return description;
}
////////////////
public void setDescription(String desc)
{
if(desc==null)
	description=new String("All Files(*.*)");
else
	description=new String(desc);
}
////////////////
public void setExtension(String ext)
{
if(ext==null)
	{extension=null;  return;}

extension=new String(ext).toLowerCase();
if(!ext.startsWith("."))
	extension="."+extension;
}
////////////////
}
/***************************************************/