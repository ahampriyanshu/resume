//package p1;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/***************************************************/
class LookAndFeelDemo extends JFrame
{
JLabel myLabel;
JMenuBar jmb;
JMenu fileMenu;

LookAndFeelDemo()
{
super("Look and Feel Demo");
add(myLabel=new JLabel("This is a Label"));
add(new JButton("Button")); 
add(new JCheckBox("CheckBox"));
add(new JRadioButton("RadioButton"));
setLayout(new FlowLayout());
setSize(350,350);
setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
jmb=new JMenuBar();
setJMenuBar(jmb);
fileMenu=new JMenu("Look and Feel");
jmb.add(fileMenu);
LookAndFeelMenu.createLookAndFeelMenuItem(fileMenu,this);
setVisible(true);
}
////////////////////////

///////////////////////
public static void main(String[] args)
{
new LookAndFeelDemo();
}
////////////////////////
}
/************************/
public class LookAndFeelMenu
{

public static void createLookAndFeelMenuItem(JMenu jmenu,Component cmp)
{
final UIManager.LookAndFeelInfo[] infos=UIManager.getInstalledLookAndFeels();

JRadioButtonMenuItem rbm[]=new JRadioButtonMenuItem[infos.length];
ButtonGroup bg=new ButtonGroup();
JMenu tmp=new JMenu("Change Look and Feel");
tmp.setMnemonic('C');
for(int i=0; i<infos.length; i++)
{
rbm[i]=new JRadioButtonMenuItem(infos[i].getName());
rbm[i].setMnemonic(infos[i].getName().charAt(0));
tmp.add(rbm[i]);
bg.add(rbm[i]);
rbm[i].addActionListener(new LookAndFeelMenuListener(infos[i].getClassName(),cmp));
}

rbm[0].setSelected(true);
jmenu.add(tmp);

}

}
/**************************/
class LookAndFeelMenuListener implements ActionListener
{
String classname;
Component jf;
/////////////////////
LookAndFeelMenuListener(String cln,Component jf)
{
this.jf=jf;
classname=new String(cln);
}
/////////////////////
public void actionPerformed(ActionEvent ev)
{
try
{
UIManager.setLookAndFeel(classname);
SwingUtilities.updateComponentTreeUI(jf);
}
catch(Exception e){System.out.println(e);}
}
///////////////////////////////
}
/*************************/