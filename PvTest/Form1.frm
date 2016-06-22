VERSION 5.00
Object = "{50F16B18-467E-11D1-8271-00C04FC3183B}#1.0#0"; "shimgvw.dll"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4980
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8100
   LinkTopic       =   "Form1"
   ScaleHeight     =   4980
   ScaleWidth      =   8100
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton bLoad 
      Caption         =   "Load"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   4440
      Width           =   2055
   End
   Begin VB.TextBox tbfp 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Text            =   """C:\Documents and Settings\All Users\Documents\My Pictures\Sample Pictures\Water lilies.jpg"""
      Top             =   3960
      Width           =   7695
   End
   Begin PREVIEWLibCtl.Preview Preview1 
      Height          =   3735
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   7815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub bLoad_Click()
    Preview1.Show Replace(tbfp.Text, """", "")
End Sub
