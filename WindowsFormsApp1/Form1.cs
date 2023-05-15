using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using My_dll;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        Json json = new Json();
        string txtname = "";
        public Form1()
        {
            InitializeComponent();
            richTextBox1.ReadOnly = false;

            richTextBox2.ReadOnly = false;
            richTextBox2.BackColor = Color.White;
            richTextBox3.ReadOnly = false;
            richTextBox3.BackColor = Color.White;
        }

        private void Open_Button(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            if(openFile.ShowDialog() == DialogResult.OK ) 
            {
                string txt = openFile.FileName.ToString();
                txtname = txt;
                json.load(txtname);
                richTextBox1.Text = json.getString();
            }
        }
        private void Save_Button(object sender, EventArgs e)
        {
            if (txtname != "")
                json.Save(txtname);
        }
        private void Add_Button(object sender, EventArgs e)
        {
            if (richTextBox2.Text != "" && richTextBox2.Text != "")
            {
                json.addVal(richTextBox2.Text, richTextBox3.Text);
                richTextBox1.Text = json.getString();
            }
        }
        private void Add_New_Button(object sender, EventArgs e)
        {
            if (richTextBox2.Text != "" && richTextBox2.Text != "")
            {
                json.Add_new(richTextBox2.Text, richTextBox3.Text);
                richTextBox1.Text = json.getString();
            }
        }
    }
}
