
import sys
from pathlib import Path
import re



PROJ_PATH : Path = Path(__file__).resolve().parent.resolve().parent.resolve()
MAIN_FILE_PATH : Path = PROJ_PATH / "sources" / "main.cpp"
SOLUTIONS_DIR : Path = PROJ_PATH / "sources" / "solutions"
GENERATED_FILE_DIR : Path = PROJ_PATH / "submit"



def error(errorString):
    print(errorString, file=sys.stderr)
    exit(1)


def searchSolutionHeader(solutionsDir: Path, solutionType: str) -> Path | None:
    pattern = re.compile(rf"\b(class|struct)\s+{re.escape(solutionType)}\b")
    
    for file_path in solutionsDir.rglob("*.hpp"):
        try:
            with file_path.open("r", encoding="utf-8", errors="ignore") as file:
                for line in file:
                    if pattern.search(line):
                        return file_path
        except (PermissionError, OSError):
            continue
            
    return None


def findSolutionType(filePath : Path) -> str:
    mainFileContent = filePath.read_text()

    pattern = r"TestRunner\s*<\s*([^>]+)\s*>"

    match = re.search(pattern, mainFileContent)

    if not match:
        return None

    return match.group(1).strip()


def generateBuild(className: str, headerPath : Path, generatedBuildFilePath : Path):
    generatedFileDir : Path = generatedBuildFilePath.parent.resolve()

    if not generatedFileDir.exists():
        error(f"Invalid directory provided for generated file: {generatedFileDir}")

    try:
        headerContent = headerPath.read_text()
        
        mainFunctionContent = f"""
int main() {{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    {className} sol{{}};
    sol.ProcessInput();
    sol.Solve();
    sol.ShowOutput();
}}
"""
        generatedBuildFilePath.write_text(headerContent + "\n" + mainFunctionContent)
        print(f"Successfully generated file at: {generatedBuildFilePath}")

    except Exception as e:
        error(f"Failed to generate build file: {e}")


if __name__ == "__main__":
    if not MAIN_FILE_PATH.exists():
        error(f"Failed to find main file at '{MAIN_FILE_PATH}'")

    if not SOLUTIONS_DIR.exists():
        error(f"Failed to find solutions directory at '{SOLUTIONS_DIR}'")

    solutionType = findSolutionType(MAIN_FILE_PATH)

    if not solutionType:
        error(f"Unable to find solution type in file '{MAIN_FILE_PATH}'")
    
    headerPath = searchSolutionHeader(SOLUTIONS_DIR, solutionType)

    if not headerPath:
        error(f"Unable to find '{solutionType}' in solution directory '{SOLUTIONS_DIR}'")

    generatedFileName = solutionType + ".cpp"
    GENERATED_FILE_DIR.mkdir(parents=True, exist_ok=True)
    generateBuild(solutionType, headerPath, GENERATED_FILE_DIR / generatedFileName)
    