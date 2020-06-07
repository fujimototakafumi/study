using System;
using System.Linq;
using System.Xml.Linq;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace SIM
{
    class MbtFloodWatch
    {

        protected class TankInfo {
            float TankVolume;
            float TankMax;

            public TankInfo(float volume,float tankMax) {
                TankVolume = volume;
                TankMax = tankMax;
            }

            public bool IsFlood => TankMax < TankVolume;
        }

        IEnumerable<XElement> elements;

        bool isEmpSw = true;
        bool isWatchexceptSw = false;
        bool isWatchexceptSw5 = false;
        bool isEmpSw67 = false;
        bool isEmpSw7 = false;

        float TankVolumeLeft1 = 10;
        float TankVolumeLeft2 = 11;
        float TankVolumeLeft3 = 12;
        float TankVolumeLeft4 = 13;
        float TankVolumeLeft6 = 15;

        float TankVolumeRight1 = 16;
        float TankVolumeRight2 = 17;
        float TankVolumeRight3 = 18;
        float TankVolumeRight4 = 19;
        float TankVolumeRight6 = 21;
        float TankVolume7 = 22;
        float TankVolumeNT = 23;

        List<TankInfo> MbtTankVolumeListLeft = new  List<TankInfo>();
        List<TankInfo> MbtTankVolumeListRight = new List<TankInfo>();
        bool[] IsfloodWatch = new bool[8];//

        public MbtFloodWatch(){


            var elements = XDocument.Load("MbtFloodWatch.xml");
            var mbtTankListLeft = elements.Root.Descendants("TankMaxLeft").ToList();
            var mbtTankListRight = elements.Root.Descendants("TankMaxRight").ToList();

            int idx = 0;
            MbtTankVolumeListLeft.Add(new TankInfo(TankVolumeLeft1, float.Parse(mbtTankListLeft[idx++].Value)));
            MbtTankVolumeListLeft.Add(new TankInfo(TankVolumeLeft2, float.Parse(mbtTankListLeft[idx++].Value)));
            MbtTankVolumeListLeft.Add(new TankInfo(TankVolumeLeft3, float.Parse(mbtTankListLeft[idx++].Value)));
            MbtTankVolumeListLeft.Add(new TankInfo(TankVolumeLeft4, float.Parse(mbtTankListLeft[idx++].Value)));
            MbtTankVolumeListLeft.Add(new TankInfo(TankVolumeLeft6, float.Parse(mbtTankListLeft[idx++].Value)));

            idx = 0;
            MbtTankVolumeListRight.Add(new TankInfo(TankVolumeRight1, float.Parse(mbtTankListRight[idx++].Value)));
            MbtTankVolumeListRight.Add(new TankInfo(TankVolumeRight2, float.Parse(mbtTankListRight[idx++].Value)));
            MbtTankVolumeListRight.Add(new TankInfo(TankVolumeRight3, float.Parse(mbtTankListRight[idx++].Value)));
            MbtTankVolumeListRight.Add(new TankInfo(TankVolumeRight4, float.Parse(mbtTankListRight[idx++].Value)));
            MbtTankVolumeListRight.Add(new TankInfo(TankVolumeRight6, float.Parse(mbtTankListRight[idx++].Value)));


        }

        public void MbtFloodWach_Init()
        {


          


            //tankMaxLeft.Va

            //foreach (var element in elements)
            //{
            //var name =  element.Element("name");
            //Console.WriteLine(element.Value);
            //}


        }

        public void MbtFloodWach_Main()
        {

            if (isEmpSw) {

                if (!isWatchexceptSw) {

                    for(int i =0;i<5; i++)
                    {
                        if (isWatchexceptSw5) continue;
                        IsfloodWatch[i] = MbtTankVolumeListRight.[i].IsFlood | MbtTankVolumeListLeft.[i].IsFlood;
                    }
                
                }
            }
        }
    }

    class SimMain
    {
        static void Main(string[] args)
        {
            MbtFloodWatch exe = new MbtFloodWatch();
            exe.MbtFloodWach_Init();
            exe.MbtFloodWach_Main();
            Console.WriteLine("Hello World!");
        }
    }
}
