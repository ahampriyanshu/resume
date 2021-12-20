//package p1;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
/******************************************************/
class FontDemo extends JFrame
{
FontChooser dialog=null; 
JTextArea ta;
JButton fontButton;

FontDemo()
{
super("Font");

ta=new JTextArea(7,20);
fontButton=new JButton("Set Font");

ActionListener ac=new ActionListener()
{
public void actionPerformed(ActionEvent ev)
{
if(dialog==null)
	dialog=new FontChooser(ta.getFont());
if(dialog.showDialog(FontDemo.this,"Choose a font"))
	{
	FontDemo.this.ta.setFont(dialog.createFont());
	}
}
};
fontButton.addActionListener(ac);

add(ta,BorderLayout.CENTER);
add(fontButton,BorderLayout.SOUTH);

setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
setBounds(50,50,400,400);
ta.append("Hello dear. how r u?");
ta.append("\n\n A quick brown fox jumps over the lazy dog.");
ta.append("\n\n0123456789");
ta.append("\n~!@#$%^&*()_+|?><");
setVisible(true);
}
////////////////////////////////
public static void main(String[] args)
{
new FontDemo();
}

}
/******************************************************/
public class FontChooser extends JPanel //implements ActionListener
{
private Font thisFont;

private JList jFace, jStyle, jSize;

private JDialog dialog;
private JButton okButton;

JTextArea tf;

private boolean ok;

public FontChooser(Font withFont)
{
thisFont=withFont;

////////////////////
String[] fontNames=
	GraphicsEnvironment
	.getLocalGraphicsEnvironment()
	.getAvailableFontFamilyNames();
jFace=new JList(fontNames); jFace.setSelectedIndex(0);

jFace.addListSelectionListener(new ListSelectionListener()
{public void valueChanged(ListSelectionEvent ev){tf.setFont(createFont());}});

String[] fontStyles={"Regular","Italic","Bold","Bold Italic"};
jStyle=new JList(fontStyles);jStyle.setSelectedIndex(0); 

jStyle.addListSelectionListener(new ListSelectionListener()
{public void valueChanged(ListSelectionEvent ev){tf.setFont(createFont());}});

String[] fontSizes=new String[30];
for(int j=0; j<30; j++)
	fontSizes[j]=new String(10+j*2+"");
jSize=new JList(fontSizes); jSize.setSelectedIndex(0); 

jSize.addListSelectionListener(new ListSelectionListener()
{public void valueChanged(ListSelectionEvent ev){tf.setFont(createFont());}});

JPanel jpLabel=new JPanel();
jpLabel.setLayout(new GridLayout(1,3));

jpLabel.add(new JLabel("Font",JLabel.CENTER));
jpLabel.add(new JLabel("Font Style",JLabel.CENTER));
jpLabel.add(new JLabel("Size",JLabel.CENTER));

JPanel jpList=new JPanel();
jpList.setLayout(new GridLayout(1,3));

jpList.add(new JScrollPane(jFace));
jpList.add(new JScrollPane(jStyle));
jpList.add(new JScrollPane(jSize));

okButton=new JButton("OK");
JButton cancelButton=new JButton("Cancel");

okButton.addActionListener(
new ActionListener()
{
public void actionPerformed(ActionEvent ev)
{
ok=true;
FontChooser.this.thisFont=FontChooser.this.createFont();
dialog.setVisible(false);
}
});

cancelButton.addActionListener(
new ActionListener()
{
public void actionPerformed(ActionEvent ev)
{
dialog.setVisible(false);
}
});

JPanel jpButton=new JPanel();
jpButton.setLayout(new FlowLayout());
jpButton.add(okButton);
jpButton.add(new JLabel("          "));//dummy Label
jpButton.add(cancelButton);

tf=new JTextArea(5,30);
JPanel jpTextField=new JPanel();
jpTextField.add(new JScrollPane(tf));

JPanel centerPanel=new JPanel();
centerPanel.setLayout(new GridLayout(2,1));
centerPanel.add(jpList);
centerPanel.add(jpTextField);

setLayout(new BorderLayout());
add(jpLabel,BorderLayout.NORTH);
add(centerPanel,BorderLayout.CENTER);
add(jpButton,BorderLayout.SOUTH);
add(new JLabel("  "),BorderLayout.EAST);//dummy label
add(new JLabel("  "),BorderLayout.WEST);//dummy label

tf.setFont(thisFont);
tf.append("\nA quick brown fox jumps over the lazy dog.");
tf.append("\n0123456789");
tf.append("\n~!@#$%^&*()_+|?><\n");

}
//////////////////////////
public Font createFont()
{
Font fnt=thisFont;
int fontstyle=Font.PLAIN;
int x=jStyle.getSelectedIndex();

switch(x)
{
case 0:
	fontstyle=Font.PLAIN;	break;
case 1:
	fontstyle=Font.ITALIC;	break;
case 2:
	fontstyle=Font.BOLD;	break;
case 3:
	fontstyle=Font.BOLD+Font.ITALIC;	break;
}

int fontsize=Integer.parseInt((String)jSize.getSelectedValue());
String fontname=(String)jFace.getSelectedValue();

fnt=new Font(fontname,fontstyle,fontsize);

return fnt;

}
//////////////////////////////////
public boolean showDialog(Component parent, String title)
{
ok=false;

Frame owner=null;
if(parent instanceof Frame) 
	owner=(Frame)parent;
else
	owner=(Frame)SwingUtilities.getAncestorOfClass(Frame.class,parent);
if(dialog==null || dialog.getOwner()!=owner)
{
dialog=new JDialog(owner,true);
dialog.add(this);
dialog.getRootPane().setDefaultButton(okButton);
dialog.setSize(400,325);
}

dialog.setTitle(title);
dialog.setVisible(true);
//System.out.println(dialog.getWidth()+" "+dialog.getHeight());
return ok;
}
//////////////////////////////
}