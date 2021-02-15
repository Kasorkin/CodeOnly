using System;
using System.Drawing.Text;

namespace ds.test.impl
{
    /// <summary>
    /// Требуемый интерфейс
    /// </summary>
    public interface IPlugin
    {
        string PluginName { get; }
        string Version { get; }
        System.Drawing.Image Image { get; }
        string Description { get; }
        int Run(int input1, int input2);
    }
    /// <summary>
    /// Асбтрактный класс, частично реализующий интерфейс IPlugin
    /// </summary>
    abstract class Plugin : IPlugin
    {
        public abstract string PluginName { get; }
        public abstract string Version { get; }
        public abstract System.Drawing.Image Image { get; }
        public abstract string Description { get; }
        public abstract int Run(int input1, int input2);
    }

    /// <summary>
    /// Плагин суммы, наследуется от абстрактного класса Plugin
    /// </summary>
    internal class PluginSumm : Plugin
    {
        private readonly string name = "PluginSumm";
        private readonly string version = "0.1";
        private readonly string description = "Просто сумма";
        private System.Drawing.Image image = ds.test.impl.Properties.Resources._111;

        public override string PluginName => name;
        public override string Version => version;
        public override System.Drawing.Image Image => image;
        public override string Description => description;

        public override int Run(int input1, int input2)
        {
            int res = 0;
            try
            {
                res = checked(input1 + input2);
            }
            catch
            {
                Console.WriteLine("Ошибка перевыполнения, возвращен 0");
                return 0;
            }
            return res;
        }
    }
    /// <summary>
    /// Плагин разности, наследуется от абстрактного класса Plugin
    /// </summary>
    internal class PluginMinus : Plugin
    {
        private readonly string name = "PluginMinus";
        private readonly string version = "0.1";
        private readonly string description = "Просто вычитание";
        private readonly System.Drawing.Image image = ds.test.impl.Properties.Resources._222;

        public override string PluginName => name;
        public override string Version => version;
        public override System.Drawing.Image Image => image;
        public override string Description => description;

        public override int Run(int input1, int input2)
        {
            int res = 0;
            try
            {
                res = checked(input1 - input2);
            }
            catch
            {
                Console.WriteLine("Ошибка перевыполнения, возвращен 0 ");
                return 0;
            }
            return res;
        }
    }
    /// <summary>
    /// Плагин умножения, наследуется от абстрактного класса Plugin
    /// </summary>
    internal class PluginMult : Plugin
    {
        private readonly string name = "PluginMult";
        private readonly string version = "0.1";
        private readonly string description = "Просто умножение";
        private readonly System.Drawing.Image image = ds.test.impl.Properties.Resources._333;

        public override string PluginName => name;
        public override string Version => version;
        public override System.Drawing.Image Image => image;
        public override string Description => description;

        public override int Run(int input1, int input2)
        {
            return input1 * input2;
        }
    }
    /// <summary>
    /// Плагин деления, наследуется от абстрактного класса Plugin
    /// </summary>
    internal class PluginDiv : Plugin
    {
        private readonly string name = "PluginDiv";
        private readonly string version = "0.1";
        private readonly string description = "Просто деление";
        private readonly System.Drawing.Image image = ds.test.impl.Properties.Resources._444;

        public override string PluginName => name;
        public override string Version => version;
        public override System.Drawing.Image Image => image;
        public override string Description => description;

        public override int Run(int input1, int input2)
        {
            int res = 0;
            try
            {
                res = input1 / input2;
            }
            catch
            {
                Console.WriteLine("Ошибка деления, возвращен 0");
                return 0;
            }
            return res;
        }
    }
    /// <summary>
    /// Статический класс Plugins, содержит в себе интерфейс IPluginFactory и его реализацию
    /// </summary>
    public static class Plugins
    {
        /// <summary>
        /// Непосредственно сам интерфейс IPluginFactory
        /// </summary>
        private interface IPluginFactory
        {
            int PluginsCount { get; }
            string[] GetPluginNames { get; }
            IPlugin GetPlugin(string pluginName);
        }
        /// <summary>
        /// Класс Programm реализует интерфейс IPluginFactory
        /// </summary>
        public class Programm : IPluginFactory
        {
            public int PluginsCount => 4;
            public string[] GetPluginNames 
            {
                get
                {
                    string[] _names = {"PluginSumm", "PluginDiv", "PluginMult", "PluginMinus" };
                    return _names;
                }
            }
            public IPlugin GetPlugin(string pluginName)
            {
                switch (pluginName)
                {
                    case "PluginSumm":
                        return new PluginSumm();
                    case "PluginDiv":
                        return new PluginDiv();
                    case "PluginMult":
                        return new PluginMult();
                    case "PluginMinus":
                        return new PluginMinus();
                    default:
                        {
                            Console.WriteLine("Ошибка, такой плагин отсутствует, возвращен null");
                            return null;
                        }
                }
            }
        }
    }
}
