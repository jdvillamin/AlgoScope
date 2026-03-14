import os
import re
from openai import OpenAI
from .prompt_header import PROMPT_HEADER

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))


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


def instrument_code(code):
    numbered_code = add_line_numbers(code)
    prompt = build_instrumentation_prompt(numbered_code)

    response = client.chat.completions.create(
        model="gpt-4.1",
        temperature=0,
        messages=[
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
    )

    instrumented = response.choices[0].message.content
    instrumented = clean_markdown(instrumented)
    instrumented = remove_line_numbers(instrumented)

    return instrumented
