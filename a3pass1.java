import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedHashMap;

public class Pass1 {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("input.asm"));
        
        FileWriter mntWriter = new FileWriter("mnt.txt");
        FileWriter mdtWriter = new FileWriter("mdt.txt");
        FileWriter kpdtWriter = new FileWriter("kpdt.txt");
        FileWriter pntWriter = new FileWriter("pntab.txt");
        FileWriter intermediateWriter = new FileWriter("ic.txt");

        LinkedHashMap<String, Integer> parameterTable = new LinkedHashMap<>();
        String currentLine;
        String macroName = null;
        int mdtPointer = 1, kpdtPointer = 0, paramCount = 1, positionalParams = 0, keywordParams = 0, macroFlag = 0;

        while ((currentLine = reader.readLine()) != null) {
            String[] lineParts = currentLine.split("\\s+");
            if (lineParts[0].equalsIgnoreCase("MACRO")) {
                macroFlag = 1;
                currentLine = reader.readLine();
                lineParts = currentLine.split("\\s+");
                macroName = lineParts[0];

                if (lineParts.length <= 1) {
                    mntWriter.write(lineParts[0] + "\t" + positionalParams + "\t" + keywordParams + "\t" + mdtPointer + "\t" + (keywordParams == 0 ? kpdtPointer : (kpdtPointer + 1)) + "\n");
                    continue;
                }

                for (int i = 1; i < lineParts.length; i++) {
                    lineParts[i] = lineParts[i].replaceAll("[&,]", "");
                    if (lineParts[i].contains("=")) {
                        keywordParams++;
                        String[] keywordParam = lineParts[i].split("=");
                        parameterTable.put(keywordParam[0], paramCount++);
                        kpdtWriter.write(keywordParam[0] + "\t" + (keywordParam.length == 2 ? keywordParam[1] : "-") + "\n");
                    } else {
                        parameterTable.put(lineParts[i], paramCount++);
                        positionalParams++;
                    }
                }

                mntWriter.write(lineParts[0] + "\t" + positionalParams + "\t" + keywordParams + "\t" + mdtPointer + "\t" + (keywordParams == 0 ? kpdtPointer : (kpdtPointer + 1)) + "\n");
                kpdtPointer += keywordParams;

            } else if (lineParts[0].equalsIgnoreCase("MEND")) {
                mdtWriter.write(currentLine + "\n");
                macroFlag = keywordParams = positionalParams = 0;
                mdtPointer++;
                paramCount = 1;

                pntWriter.write(macroName + ":\t");
                Iterator<String> iterator = parameterTable.keySet().iterator();
                while (iterator.hasNext()) {
                    pntWriter.write(iterator.next() + "\t");
                }
                pntWriter.write("\n");
                parameterTable.clear();

            } else if (macroFlag == 1) {
                for (String part : lineParts) {
                    if (part.contains("&")) {
                        part = part.replaceAll("[&,]", "");
                        mdtWriter.write("(P," + parameterTable.get(part) + ")\t");
                    } else {
                        mdtWriter.write(part + "\t");
                    }
                }
                mdtWriter.write("\n");
                mdtPointer++;
            } else {
                intermediateWriter.write(currentLine + "\n");
            }
        }

        reader.close();
        mdtWriter.close();
        mntWriter.close();
        intermediateWriter.close();
        pntWriter.close();
        kpdtWriter.close();

        System.out.println("Macro Pass 1 Processing completed successfully. :)");
    }
}
