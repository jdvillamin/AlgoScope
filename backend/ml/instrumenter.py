import os
import re
from openai import OpenAI
from .prompt_header import PROMPT_HEADER

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))
INSTRUMENTATION_MODEL = os.getenv(
    "ALGOSCOPE_INSTRUMENTATION_MODEL",
    "ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd",
)
INSTRUMENTATION_PROMPT_MODE = os.getenv(
    "ALGOSCOPE_INSTRUMENTATION_PROMPT_MODE",
    "sft" if INSTRUMENTATION_MODEL.startswith("ft:") else "prompt",
)


def add_line_numbers(code):
    lines = code.split("\n")
    numbered = []

    for i, line in enumerate(lines, start=1):
        numbered.append(f"{i}: {line}")

    return "\n".join(numbered)


def remove_line_numbers(code):
    cleaned = []

    for line in code.split("\n"):
        line = re.sub(r"^\s*\d+:\s*", "", line)
        cleaned.append(line)

    return "\n".join(cleaned)


def clean_markdown(text):
    text = re.sub(r"```c", "", text)
    text = re.sub(r"```", "", text)
    return text.strip()


def build_instrumentation_prompt(numbered_code):
    return f"""{PROMPT_HEADER}

==================================================
SOURCE CODE
==================================================

{numbered_code}
""".strip()


def build_messages(code):
    if INSTRUMENTATION_PROMPT_MODE == "sft":
        return [
            {
                "role": "system",
                "content": (
                    "You are a strict C instrumentation engine. Insert tracer calls into the C "
                    "program while preserving every original source line exactly. Output only "
                    "valid C code."
                )
            },
            {
                "role": "user",
                "content": f"Instrument this C program:\n\n{code}"
            }
        ]

    numbered_code = add_line_numbers(code)
    prompt = build_instrumentation_prompt(numbered_code)
    return [
        {
            "role": "system",
            "content": (
                "You are a strict C instrumentation engine. "
                "Preserve the full original source code exactly. "
                "Only insert trace lines before or after existing source lines."
            )
        },
        {
            "role": "user",
            "content": prompt
        }
    ]


def instrument_code(code):
    response = client.chat.completions.create(
        model=INSTRUMENTATION_MODEL,
        temperature=0,
        messages=build_messages(code)
    )

    instrumented = response.choices[0].message.content
    instrumented = clean_markdown(instrumented)
    if INSTRUMENTATION_PROMPT_MODE != "sft":
        instrumented = remove_line_numbers(instrumented)

    return instrumented
