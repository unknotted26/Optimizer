using System;
//using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using opti.DS;
namespace Optimizer.WPF
{
    using Microsoft.Win32;
    //using opti.DS.CLI; // This requires a public, non-template class within the namespace    
    
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var fileOpenDialog = new OpenFileDialog
            {
                CheckFileExists = true,
                Filter = "Native Library|Optimizer.Cpp.List.dll",
                InitialDirectory = "C:\\Users\\kp12g_000\\Documents\\Visual Studio 2017\\Projects\\Optimizer\\Debug",
                FileName = "\\Optimizer.Cpp.List.dll"
            };

            opti.DS.CLI.testClass.InitializeLibrary(fileOpenDialog.InitialDirectory + fileOpenDialog.FileName);
            using (var wrapper = new  opti.DS.CLI.ListInt())//opti.DS.CLI.testClass())
            {
                wrapper.PushFront(1);
                wrapper.PushFront(2);
                wrapper.PushBack(3);

                MessageBox.Show($"ListInt - { wrapper.About() } - { wrapper.Front() } - { wrapper.Back() }");
                //wrapper._list.InitTestValues();
                //MessageBox.Show($"{wrapper.GetType()} - {wrapper._list.About()} - {wrapper._list.Front()}");
            }
            
            using (var wrapper = new opti.DS.CLI.TemplateWrapper<int>())
            {
                //wrapper.InitTestValues();
                //opti.DS.CLI.TemplateWrapper<int> t = new opti.DS.CLI.TemplateWrapper<int>(); 
                //MessageBox.Show($"{wrapper.Front()}");
            }

           
        }
    }
}
