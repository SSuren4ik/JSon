using My_dll;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        Json json = new Json();
        string txtname = "";
        public Form1()
        {
            InitializeComponent();
            richTextBox1.ReadOnly = true;
            richTextBox4.ReadOnly = true;

            richTextBox2.ReadOnly = false;
            richTextBox2.BackColor = Color.White;
            richTextBox3.ReadOnly = false;
            richTextBox3.BackColor = Color.White;
        }

        private void Open_Button(object sender, EventArgs e)
        {
            richTextBox1.ReadOnly = false;
            OpenFileDialog openFile = new OpenFileDialog();
            if(openFile.ShowDialog() == DialogResult.OK ) 
            {
                string txt = openFile.FileName.ToString();
                txtname = txt;
                json.load(txtname);
                richTextBox1.Text = json.getString();
                richTextBox4.Text = json.getStringCurrent();
            }
            richTextBox1.ReadOnly = true;
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
                richTextBox4.Text = json.getStringCurrent();
            }
        }
        private void Add_New_Button(object sender, EventArgs e)
        {
            if (richTextBox2.Text != "" && richTextBox2.Text != "")
            {
                json.Add_new(richTextBox2.Text, richTextBox3.Text);
                richTextBox1.Text = json.getString();
                richTextBox4.Text = json.getStringCurrent();
            }
        }

        private void Next_Button(object sender, EventArgs e)
        {
                json.Next();
            richTextBox4.Text= json.getStringCurrent();
        }

        private void Back_Button(object sender, EventArgs e)
        {
            json.Back();
            richTextBox4.Text = json.getStringCurrent();
        }

        private void Down_Button(object sender, EventArgs e)
        {
            json.Down();
            richTextBox4.Text = json.getStringCurrent();
        }
    }
}
